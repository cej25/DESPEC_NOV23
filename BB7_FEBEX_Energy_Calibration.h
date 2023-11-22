#ifndef BB7_FEBEX_ENERGY_CALIB_H
#define BB7_FEBEX_ENERGY_CALIB_H

#include <string>
#include <fstream>
#include <iostream>

class BB7_FEBEX_Energy_Calibration
{
    private:
        //double calib_coeffs[][];

        std::string filename;
        
        void load_Calibration_File();
    
    public:
        BB7_FEBEX_Energy_Calibration();
        ~BB7_FEBEX_Energy_Calibration();

        double Calibrate_FEBEX_E(double, int);
};

#endif