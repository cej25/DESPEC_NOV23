#include "BB7_TWINPEAKS_Detector_System.h"

// using namespace std;

BB7_TWINPEAKS_Detector_System::BB7_TWINPEAKS_Detector_System()
{
    get_Calib_type();
    cal_count = 0;

    Calibration_Done = false;

    BB7_TAMEX_Calibration = new BB7_TAMEX_Calibration(CALIBRATE);

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
        ch_ID_edge[i] = new double[200];

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

    delete BB7_TAMEX_Calibration
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
}