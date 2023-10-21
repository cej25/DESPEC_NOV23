#ifndef BB7_FEBEX_DETECTOR_SYSTEM_H
#define BB7_FEBEX_DETECTOR_SYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>

#include "FEBEX.h"

#include "Detector_System.cxx"

typedef unsigned long long ULong64_t;

class BB7_FEBEX_Detector_System : public Detector_System
{
    private:

        int module_id;
        int num_channels;
        int channel_id;

        int *pdata;

        int max_hits;
        int num_modules;

        int Hits;
        int* Strip;
        int* Side;
        ULong64_t* Sum_Time;
        ULong64_t* Chan_Time;
        double* Chan_Energy;
        ULong64_t* Chan_CF;
        bool* Overflow;
        bool* Pileup;

        ULong64_t tmp_Sum_Time;
        ULong64_t tmp_EventTime_hi;
        ULong64_t tmp_ChanTime_hi;
        int tmp_Pileup;
        int tmp_Hit_Pattern;
        
        // module_id, channel_id -> side, strip
        std::map<std::pair<int,int>, std::pair<int,int>> BB7_FEBEX_Map;
        
        void load_board_channel_file();
        void reset_fired_channels();
        void Calibrate_FEBEX();
    
    public:
        BB7_FEBEX_Detector_System();
        ~BB7_FEBEX_Detector_System();

        void Process_MBS(TGo4MbsSubEvent* psubevt) {};
        void Process_MBS(int*);
        void get_Event_data(Raw_Event*);
        int* get_pdata();

        // needed for Detector System
        bool calibration_done() { return false; }
        void write() { return; }
        void set_Gain_Match_Filename(std::string) { return; }
        bool do_gain_matching(int ts_ns) { return 1; }
        unsigned long next_ts_for_update() { return 1; }

};

#endif