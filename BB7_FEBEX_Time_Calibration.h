#ifndef BB7_FEBEX_TIME_CALIB_H
#define BB7_FEBEX_TIME_CALIB_H

#include <string>
#include <fstream>
#include <iostream>

typedef unsigned long ULong;

class BB7_FEBEX_Time_Calibration
{
    private:
        double calib_coeffs_sum[36];
        double calib_coeffs_channels[36];
    
    public:
        BB7_FEBEX_Time_Calibration();
        ~BB7_FEBEX_Time_Calibration();
    
        void load_Calibration_File();
        ULong Calibrate_FEBEX_Sum_T(ULong, int);
        ULong Calibrate_FEBEX_Chan_T(ULong, int);
};

#endif