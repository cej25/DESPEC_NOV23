#include "BB7_TWINPEAKS_Detector_System.h"

// using namespace std;

BB7_TWINPEAKS_Detector_System::BB7_TWINPEAKS_Detector_System()
{
    get_Calib_type();
    cal_count = 0;

    Calibration_Done = false;

    BB7_TAMEX_Calibration = new BB7_TAMEX_Calibrator(CALIBRATE);

    iterator = new int[200];
    for (int i = 0; i < 200; i++)
    {
        iterator[i] = 0;
    }

    tamex_iter = 0;
    lead_arr = new int*[200];
    leading_hits = new int*[200];
    trailing_hits = new int*[200];

    coarse_T = new double[200];
    fine_T = new double[200];
    ch_ID = new unsigned int[200];

    edge_coarse = new double*[200];
    edge_fine = new double*[200];
    ch_ID_edge = new unsigned int*[200];

    for (int i = 0; i < 200; i++)
    {
        edge_coarse[i] = new double[200];
        edge_fine[i] = new double[200];
        ch_ID_edge[i] = new unsigned int[200];

        lead_arr[i] = new int[200];
        leading_hits[i] = new int[200];
        trailing_hits[i] = new int[200];
    }
}

BB7_TWINPEAKS_Detector_System::~BB7_TWINPEAKS_Detector_System()
{
    for (int i = 0; i < 200; i++)
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
    RAW->set_DATA_PLASTIC_TWINPEAKS(iterator, edge_coarse, edge_fine, ch_ID_edge, coarse_T, fine_T, tamex_iter, lead_arr);
}

void BB7_TWINPEAKS_Detector_System::Process_MBS(int* pdata)
{
    this->pdata = pdata;

    for (int i = 0; i < tamex_iter; i++) 
    {
        iterator[i] = 0;
    }
    reset_edges();
    tamex_end = false;
    tamex_iter = 0;

    while(!tamex_end)
    {
        Process_TAMEX();
        if (!tamex_end)
        {
            tamex_iter++;
        }
        this->pdata++;
    }

    if (CALIBRATE)
    {
        calibrate_ONLINE();
    }
    else
    {
        calibrate_OFFLINE();
    }
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
    if (am_fired[tamex_iter] > 3)
    {
        get_edges();
    }
    else
    {
        no_edges[tamex_iter] = true;
    }

    check_trailer();

}

void BB7_TWINPEAKS_Detector_System::skip_padding()
{   
    // CEJ: sorry but this is insane
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
    PLACE_HOLDER* Epoch_Counter = (PLACE_HOLDER*) pdata;

    // we should be doing something here...check Helena's scanner code.

    pdata++;

    TAMEX_DATA* TDC_Data = (TAMEX_DATA*) pdata;
    coarse_T[tamex_iter] = (double) TDC_Data->coarse_T;
    fine_T[tamex_iter] = (double) TDC_Data->fine_T;
    ch_ID[tamex_iter] = TDC_Data->ch_ID;

    pdata++;

}

void BB7_TWINPEAKS_Detector_System::reset_edges()
{
    for (int i = 0; i < BB7_TAMEX_MODULES; i++)
    {
        for (int j = 0; j < 200; j++)
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
    iterator[tamex_iter] = 0;

    written = false; // CEJ: i have no honest to god idea what this is for

    while (no_error_reached())
    {
        PLACE_HOLDER* TDC_Epoch_Check = (PLACE_HOLDER*) pdata;

        if (TDC_Epoch_Check->six_eight == 0x6)
        {   
            // this is an epoch...we need to do something here..
            pdata++;
            continue; 
        }

        if (TDC_Epoch_Check->six_eight != 0x6)
        {
            written = false;
        }

        TAMEX_DATA* TDC_Data = (TAMEX_DATA*) pdata;

        if (TDC_Data->leading_E == 1)
        {
            leading_hit = TDC_Data->leading_E;
            edge_coarse[tamex_iter][iterator[tamex_iter]] = (double) TDC_Data->coarse_T;
            edge_fine[tamex_iter][iterator[tamex_iter]] = (double) TDC_Data->fine_T;
            ch_ID_edge[tamex_iter][iterator[tamex_iter]] = TDC_Data->ch_ID;
            lead_arr[tamex_iter][iterator[tamex_iter]] = (TDC_Data->ch_ID % 2); // is this fast and slow?
        }

        if (TDC_Data->leading_E == 0)
        {
            leading_hit = TDC_Data->leading_E;
            edge_coarse[tamex_iter][iterator[tamex_iter]] = (double) TDC_Data->coarse_T;
            edge_fine[tamex_iter][iterator[tamex_iter]] = (double) TDC_Data->fine_T;
            ch_ID_edge[tamex_iter][iterator[tamex_iter]] = TDC_Data->ch_ID + MAX_CHA_INPUT;
        }

        iterator[tamex_iter]++;
        if (iterator[tamex_iter] > 100)
        {
            break;
        }

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

void BB7_TWINPEAKS_Detector_System::get_Calib_Type()
{
    // read a file, do something else
}

