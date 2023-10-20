#ifndef BB7_MADC_DETECTOR_SYSTEM_H
#define BB7_MADC_DETECTOR_SYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>

// calibrations??

#include "MADC32.h"

#include "Detector_System.cxx"

class BB7_MADC_Detector_System : public Detector_System
{
    private:
        // stuff
        int module_id;  // 1_2 // hopefully..maybe
        int channel_id; // 1_32 

        int* pdata;
        int adc_words;

        int max_hits;
        int num_modules;

        int* Module_ID;
        int* Side;
        int* Strip;
        int* AdcData;
        int* Hit_Pattern; // does this need to be an array? [1,0,1,1,0,0,0,1]?

    
    public:
        BB7_MADC_Detector_System();
        ~BB7_MADC_Detector_System();

        void Process_MBS(TGo4SubEvent* psubevt) {};
        void Process_MBS(int*);
        void get_Event_Data(Raw_Event*);
        int* get_pdata();

        // neede for Detector_System
        bool calibration_done() { return false; }
        void write() { return; }
        void set_Gain_Match_Filename(std::string) { return; }
        bool do_gain_matching(int ts_ns) { return 1; }
        unsigned long next_ts_for_update() { return 1; }

}



#endif