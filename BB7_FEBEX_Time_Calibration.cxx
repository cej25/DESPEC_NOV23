#include "BB7_FEBEX_Time_Calibration.h"

#include <cstdlib>

// using namespace std;

BB7_FEBEX_Time_Calibration::BB7_FEBEX_Time_Calibration()
{
    // load_Calibration_File();
}

BB7_FEBEX_Time_Calibration::~BB7_FEBEX_Time_Calibration()
{
}

void BB7_FEBEX_Time_Calibration::load_Calibration_File()
{
    // load file
}

ULong BB7_FEBEX_Time_Calibration::Calibrate_FEBEX_Sum_T(ULong Sum_T, int det_id)
{
    return Sum_T + calib_coeffs_sum[det_id];
}

ULong BB7_FEBEX_Time_Calibration::Calibrate_FEBEX_Chan_T(ULong Chan_T, int det_id)
{
    return Chan_T + calib_coeffs_channels[det_id];
}