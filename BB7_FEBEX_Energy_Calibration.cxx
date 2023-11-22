#include "BB7_FEBEX_Energy_Calibration.h"

#include <cstdlib>

// using namespace std;

BB7_FEBEX_Energy_Calibration::BB7_FEBEX_Energy_Calibration()
{
    load_Calibration_File();
}

BB7_FEBEX_Energy_Calibration::~BB7_FEBEX_Energy_Calibration()
{
}

void BB7_FEBEX_Energy_Calibration::load_Calibration_File()
{
    // load file
}

double BB7_FEBEX_Energy_Calibration::Calibrate_FEBEX_E(double e, int det_id)
{
    // do we calibrate this the same way as Ge? (Horner's method)
    
}