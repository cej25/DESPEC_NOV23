#include "BB7_TAMEX_Calibrator.h"

//using namespace std;

BB7_TAMEX_Calibrator::BB7_TAMEX_Calibrator(bool ONLINE)
{
    this->ONLINE = ONLINE;

    nbins = 600;
    min_val = 0;
    max_val = 600;

    // only for online calibration
    if (this->ONLINE)
    {
        fired = new bool*[100];
        for (int i = 0; i < 100; i++)
        {
            fired[i] = new bool[100];
            for (int j = 0; j < 100; j++)
            {
                fired[i][j] = false;
            }
        }
        char tmp_name[1000];

        Fine_Hist = new TH1D**[100];
        for (int i = 0; i < 100; i++)
        {
            Fine_Hist[i] = new TH1D*[100];
            for (int j = 0; j < 100; j++)
            {
                sprintf(tmp_name, "PDF_%d_%d", i, j);
                Fine_Hist[i][j] = new TH1D(tmp_name, tmp_name, nbins, min_val, max_val);
            }
        }
    }
    else
    {
        bins_x_arr = new double[nbins];
        Cal_arr = new double**[100];
        for (int i = 0; i < 100; i++)
        {
            Cal_arr[i] = new double*[100];
            for (int j = 0; j < 100; j++)
            {
                Cal_arr[i][j] = new double[nbins]; 
            }
        }
        fired = NULL;
        Fine_Hist = NULL;
        load_Calibration_Files();
    }
}

BB7_TAMEX_Calibrator::~BB7_TAMEX_Calibrator()
{
    if (ONLINE)
    {
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                delete Fine_Hist[i][j];
            }
            delete[] fired[i];
            delete[] Fine_Hist[i];
        }
        delete fired;
        delete Fine_Hist;
    }
    else
    {
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                if (Cal_arr[i][j])
                {
                    delete[] Cal_arr[i][j];
                }
            }
            delete[] Cal_arr[i];
            delete[] wired_tamex_ch[i];
        }
        delete[] wired_tamex_ch;
        delete[] Cal_arr;
        delete[] bins_x_arr;
    }
}

void BB7_TAMEX_Calibrator::load_Calibration_Files()
{
    // load files
}

// CEJ: fix in future...
double BB7_TAMEX_Calibrator::get_Calibration_val(double one, int two, int three)
{
    // get calibration val
}

void BB7_TAMEX_Calibrator::get_data(double** fine_T, UInt** ch_id, int tamex_iter, int* iterator)
{
    // write into corresponding root histograms
}

void BB7_TAMEX_Calibrator::ONLINE_CALIBRATION()
{
    // online calibration
}

