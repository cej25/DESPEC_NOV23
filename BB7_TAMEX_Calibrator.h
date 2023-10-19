#ifndef BB7_TAMEX_CALIBRATOR_H
#define BB7_TAMEX_CALIBRATOR_H

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>

#include <TFile.h>
#include <TH1.h>

typedef unsigned long ULong;
typedef unsigned int UInt;

class BB7_TAMEX_Calibrator
{
    private:
        bool ONLINE;
        int am_fired;
        int iter;
        int nbins;

        double min_val;
        double max_val;

        bool** fired;
        bool** wired_tamex_ch;

        double bins_x_arr;
        double*** Cal_arr;

        TH1D*** Fine_Hist;

        void load_Calibration_Files();
    
    public:
        BB7_TAMEX_Calibrator(bool);
        ~BB7_TAMEX_Calibrator();

        void get_data(double**, UInt**, int, int*);

        void ONLINE_CALIBRATION();
        double get_Calibration_val(double, int, int);
};

#endif