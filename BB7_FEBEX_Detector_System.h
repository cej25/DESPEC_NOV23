#ifndef BB7_FEBEX_DETECTOR_SYSTEM_H
#define BB7_FEBEX_DETECTOR_SYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>

#include "BB7_FEBEX_Energy_Calibration.h"
#include "BB7_FEBEX_Time_Calibration.h"

#include "FEBEX.h"

#include "Detector_System.cxx"

typedef unsigned long long ULong64_t;

class BB7_FEBEX_Detector_System : public Detector_System
{
    private:
        int max_am_dets;

        int board_id;
        int num_channels;

        int* pdata;

        ULong64_t tmp_Sum_Time;
        int tmp_Pileup;
        int tmp_Hit_Pattern;

        int* det_ids;
        int* crystal_ids;
        ULong64_t* Sum_Time;
        int* Hit_Pattern;
        ULong64_t* Chan_Time;
        double* Chan_Energy;
        ULong64_t Chan_CF;
        bool* Overflow;
        bool* Pileup;

        // CEJ: do we need traces stuff? will remove if not
        int l_cha_size;
        int l_trace_head;
        int l_trace_size;

        int l_trace_tail;
        int* trace_channel_id;
        int* trace_board_id;
        int** l_dat_fir;
        int** l_dat_sec;

        int fired_FEBEX_traces;

        std::map<std::pair<int,int>, std::pair<int,int>> BB7_Map;

        int num_channels_fired;

        int pileup_flags[BB7_FEBEX_MAX_HITS];
        int BB7_channels[BB7_FEBEX_MAX_HITS]; 
        int fired_FEBEX_amount;
        
        void load_board_channel_file();
        void reset_fired_channels();
        void Calibrate_FEBEX();

        BB7_FEBEX_Energy_Calibration* BB7_E_CALIB;
        BB7_FEBEX_Time_Calibration* BB7_T_CALIB;

    
    public:
        BB7_FEBEX_Detector_System();
        ~BB7_FEBEX_Detector_System();

        void Process_MBS(TGo4MbsSubEvent* psubevt) {};

        void Process_MBS(int*);
        void get_Event_Data(Raw_Event*);
        int* get_pdata();

        // needed for Detector System
        bool calibration_done() { return false; }
        void write() { return; }
        void set_Gain_Match_Filename(std::string) { return; }
        bool do_gain_matching(int ts_ns) { return 1; }
        unsigned long next_ts_for_update() { return 1; }
    

};