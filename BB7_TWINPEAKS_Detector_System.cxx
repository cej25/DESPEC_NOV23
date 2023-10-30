#include "BB7_TWINPEAKS_Detector_System.h"

#define DEBUG 0

// using namespace std;

BB7_TWINPEAKS_Detector_System::BB7_TWINPEAKS_Detector_System()
{
    get_calib_type();
    cal_count = 0;

    Calibration_Done = false;

    BB7_TAMEX_Calibration = new BB7_TAMEX_Calibrator(CALIBRATE);

    iterator = new int[BB7_TAMEX_MODULES];
    for (int i = 0; i < BB7_TAMEX_MODULES; i++) iterator[i] = 0;

    epoch_ch = new int*[BB7_TAMEX_MODULES];
    for (int i = 0; i < BB7_TAMEX_MODULES; i++) epoch_ch[i] = new int[BB7_TAMEX_CHANNELS * 2 + 1];

    tamex_iter = 0;
    lead_arr = new int*[BB7_TAMEX_MODULES];
    leading_hits = new int*[BB7_TAMEX_MODULES];
    trailing_hits = new int*[BB7_TAMEX_MODULES];

    coarse_T = new double[BB7_TAMEX_MODULES];
    fine_T = new double[BB7_TAMEX_MODULES];
    ch_ID = new unsigned int[BB7_TAMEX_MODULES];

    edge_coarse = new double*[BB7_TAMEX_MODULES];
    edge_fine = new double*[BB7_TAMEX_MODULES];
    ch_ID_edge = new unsigned int*[BB7_TAMEX_MODULES];

    for (int i = 0; i < BB7_TAMEX_MODULES; i++)
    {
        edge_coarse[i] = new double[BB7_TAMEX_MAX_HITS];
        edge_fine[i] = new double[BB7_TAMEX_MAX_HITS];
        ch_ID_edge[i] = new unsigned int[BB7_TAMEX_MAX_HITS];

        lead_arr[i] = new int[BB7_TAMEX_MAX_HITS];
        leading_hits[i] = new int[BB7_TAMEX_MAX_HITS];
        trailing_hits[i] = new int[BB7_TAMEX_MAX_HITS];
    }
}

BB7_TWINPEAKS_Detector_System::~BB7_TWINPEAKS_Detector_System()
{
    for (int i = 0; i < BB7_TAMEX_MAX_HITS; i++)
    {
        delete[] edge_coarse[i];
        delete[] edge_fine[i];
        delete[] ch_ID_edge[i];

        delete lead_arr[i];
        delete leading_hits[i];
        delete trailing_hits[i];
    }

    delete[] edge_coarse;
    delete[] edge_fine;
    delete[] ch_ID_edge;

    delete[] coarse_T;
    delete[] fine_T;
    delete[] ch_ID;

    delete BB7_TAMEX_Calibration;
}

void BB7_TWINPEAKS_Detector_System::get_Event_data(Raw_Event* RAW)
{
    RAW->set_DATA_BB7_TWINPEAKS(iterator, edge_coarse, edge_fine, ch_ID_edge, coarse_T, fine_T, tamex_iter, lead_arr);
}

void BB7_TWINPEAKS_Detector_System::Process_MBS(int* pdata)
{
    this->pdata = pdata;

    for (int i = 0; i < tamex_iter; i++) 
    {
        iterator[i] = 0;
        for (int j = 0; j < BB7_TAMEX_CHANNELS * 2 + 1; j++) epoch_ch[i][j] = 0;
    }
    reset_edges();
    tamex_end = false;
    tamex_iter = 0;

    while(!tamex_end)
    {
        Process_TAMEX();
        if (!tamex_end) tamex_iter++;
        this->pdata++;
    }
    
    if (CALIBRATE) calibrate_ONLINE();
    else calibrate_OFFLINE();
}

void BB7_TWINPEAKS_Detector_System::Process_TAMEX()
{
    iterator[tamex_iter] = 0;
    no_edges[tamex_iter] = false;

    written = false;

    if (tamex_iter == 0)
    {
        TRIGGER_WINDOW* window = (TRIGGER_WINDOW*) pdata;
        Pre_Trigger_Window = window->PRE_TRIGG;
        Post_Trigger_Window = window->POST_TRIGG;

        pdata++;

        skip_padding();
    }

    TAMEX_CHANNEL_HEADER* Channel_Header = (TAMEX_CHANNEL_HEADER*) pdata;

    bool ongoing = (Channel_Header->identify == 0x34) && (Channel_Header->identify_2 == 0) && (Channel_Header->sfp_id == 1 || Channel_Header->sfp_id == 0);

    if (!ongoing)
    {
        tamex_end = true;
        return;
    }
    if (tamex_iter > 0)
    {
        if (Channel_Header->Tamex_id <= tamex_id[tamex_iter - 1])
        {
            tamex_end = true;
            return;
        }
    }

    sfp_id[tamex_iter] = Channel_Header->sfp_id;
    trigger_type[tamex_iter] = Channel_Header->trigger_t;
    tamex_id[tamex_iter] = Channel_Header->Tamex_id;

    pdata++;

    TAMEX_FIRED* Tamex_Fired = (TAMEX_FIRED*) pdata;
    am_fired[tamex_iter] = (Tamex_Fired->am_fired) / 4 - 2;

    if (am_fired[tamex_iter] < 0)
    {
        std::cerr << "NEGATIVE TAMEX FIRED AMOUNT ENCOUNTERED IN BB7 LAYER...OOPS" << std::endl;
    }

    pdata++;

    TAMEX_BEGIN* TDC_Header = (TAMEX_BEGIN*) pdata;
    if (TDC_Header->aa != 0xAA)
    {
        std::cerr << "Error in TAMEX format! TDC header word not found after fired_amount" << std::endl;
        std::cerr << "TAMEX WORD: " << std::hex << *pdata << std::dec << std::endl;
    }

    pdata++;
    
    get_trigger();
    if (am_fired[tamex_iter] > 3) get_edges();
    else no_edges[tamex_iter] = true;
    
    check_trailer();

}

void BB7_TWINPEAKS_Detector_System::skip_padding()
{   
    // CEJ: strongly dislike the consistency here
    bool still_padding = true;
    while (still_padding)
    {
        PADDING* padding = (PADDING*) pdata;
        if (padding->add == 0xADD)
        {
            pdata++;
        }
        else
        {
            still_padding = false;
        }
    }
}

void BB7_TWINPEAKS_Detector_System::get_trigger()
{
    EPOCH* epoch = (EPOCH*) pdata;

    // CEJ: starting here with helena's fixes
    if (epoch->six_eight == 0x6)
    {   
        if (DEBUG) std::cout << "Epoch Data! Trigger Epoch: " << epoch->epoch_count << std::endl;
        epoch_ch[tamex_iter][0] = epoch->epoch_count;
    }

    pdata++;

    TAMEX_DATA* data = (TAMEX_DATA*) pdata;
    coarse_T[tamex_iter] = (double) data->coarse_T;
    fine_T[tamex_iter] = (double) data->fine_T;
    ch_ID[tamex_iter] = data->ch_ID;

    pdata++;

}

void BB7_TWINPEAKS_Detector_System::reset_edges()
{
    for (int i = 0; i < BB7_TAMEX_MODULES; i++)
    {
        for (int j = 0; j < BB7_TAMEX_MAX_HITS; j++)
        {
            leading_hits[i][j] = 0;
            trailing_hits[i][j] = 0;
            edge_coarse[i][j] = 131313;
            edge_fine[i][j] = 131313;
            ch_ID_edge[i][j] = 131313;
        }
    }
}

void BB7_TWINPEAKS_Detector_System::get_edges()
{   
    // done with helenas fixes
    iterator[tamex_iter] = 0;

    written = false;

    int test_counter = 0;
    int last_epoch = -1;
    int first_epoch = 0; // seemingly unused

    while (no_error_reached())
    {
        EPOCH* epoch = (EPOCH*) pdata;

        if (epoch->six_eight == 0x6)
        {   
            if (DEBUG) std::cout << "Epoch Data! Epoch: " << epoch->epoch_count << std::endl; // CEJ: presumably TAMEX.h can be adjusted
            last_epoch = epoch->epoch_count;
            pdata++;
            continue;
        }
        if (epoch->six_eight != 0x6) written = false;

        TAMEX_DATA* data = (TAMEX_DATA*) pdata;

        epoch_ch[tamex_iter][data->ch_ID] = last_epoch;

        // From HMA:
        // shift times relative to epoch for trigger for each channel
        // coarse time in units of 10ns, 2048 clocks in 1 epoch
        // subtract [(trigger epoch) - (channel epoch)] * 2048
        // data->coarse_T = data->coarse_T - ((epoch_ch[tamex_iter][0] - epoch_ch[tamex_iter][data->ch_ID]) * 2048);
        // CEJ: hmm.. helena makes the same correction twice...is this a mistake? we'll see. Commenting first out.
        leading_hit = data->leading_E;
        edge_coarse[tamex_iter][iterator[tamex_iter]] = data->coarse_T - ((epoch_ch[tamex_iter][0] - epoch_ch[tamex_iter][data->ch_ID]) * 2048);
        edge_fine[tamex_iter][iterator[tamex_iter]] = (double) data->fine_T;
        lead_arr[tamex_iter][iterator[tamex_iter]] = data->leading_E;

        if (data->leading_E == 1) ch_ID_edge[tamex_iter][iterator[tamex_iter]] = data->ch_ID;
        if (data->leading_E == 0) ch_ID_edge[tamex_iter][iterator[tamex_iter]] = data->ch_ID + MAX_CHA_INPUT;
        
        iterator[tamex_iter]++;
        written = true;
        pdata++;

    }

}

bool BB7_TWINPEAKS_Detector_System::no_error_reached()
{
    TAMEX_ERROR* error = (TAMEX_ERROR*) pdata;
    return error->error != 0xEE;
}

void BB7_TWINPEAKS_Detector_System::check_error()
{
    TAMEX_ERROR* error = (TAMEX_ERROR*) pdata;

    if (error->error != 0xEE)
    {
        std::cerr << "wrong error heading in BB7 TAMEX word: " << std::hex << *pdata << std::dec << std::endl;
        exit(0);
    }
    if (error->err_code != 0)
    {
        std::cerr << "Error (not known) in BB7 TAMEX occurred: " << std::hex << *pdata << std::dec << std::endl;
    }
}


void BB7_TWINPEAKS_Detector_System::check_trailer()
{
    pdata++; // CEJ: skips error word this time... why?

    TAMEX_TRAILER* trailer = (TAMEX_TRAILER*) pdata;

    if (trailer->trailer != 0xBB)
    {
        // std::cerr << Unknown TAMEX trailer format! << std::endl;
    }
}

void BB7_TWINPEAKS_Detector_System::calibrate_ONLINE()
{
    // calibrate
}

void BB7_TWINPEAKS_Detector_System::calibrate_OFFLINE()
{
    // calibrate
}

void BB7_TWINPEAKS_Detector_System::get_calib_type()
{
    // read a file, do something else
}

int* BB7_TWINPEAKS_Detector_System::get_pdata() { return pdata; }