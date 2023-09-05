#ifndef Germanium_DETECTOR_SYSTEM_H
#define Germanium_DETECTOR_SYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>


#include "Germanium_Energy_Calibration.h"
#include "Germanium_Time_Calibration.h"

#include "FEBEX.h"

#include "Detector_System.cxx"

typedef unsigned long long ULong64_t;

class Germanium_Detector_System : public Detector_System{


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
    ULong64_t* Chan_CF;
    bool* Overflow;
    bool* Pileup;
    
    int         l_cha_size;
    int         l_trace_head;
    int         l_trace_size;
//     int         l_dat_fir[Germanium_TRACE_LENGTH/2];
//     int         l_dat_sec[Germanium_TRACE_LENGTH/2];  
    int         l_trace_trail;
    int*        trace_channel_id;
    int*        trace_board_id;
    int**       l_dat_fir;
    int**       l_dat_sec;
    
    int fired_FEBEX_traces;
    

    std::map<std::pair<int,int>, std::pair<int,int>> Germanium_map;
    
    int num_channels_fired = 0;

    int pileup_flags[Germanium_MAX_HITS];
    int Ge_channels[Germanium_MAX_HITS];
    int fired_FEBEX_amount;
    void load_board_channel_file();
    void reset_fired_channels();
    void Calibrate_FEBEX(int);

    Germanium_Time_Calibration* Germanium_T_CALIB;
    Germanium_Energy_Calibration* Germanium_E_CALIB;


public:
    Germanium_Detector_System();
    ~Germanium_Detector_System();
    
    void Process_MBS(TGo4MbsSubEvent* psubevt){};

    void Process_MBS(int*);
    void get_Event_data(Raw_Event*);
    int* get_pdata();


    // Useless but needed for Detector_System
    bool calibration_done(){return false;}
    void write(){return;};
    void set_Gain_Match_Filename(std::string){return;};
    bool do_gain_matching(int ts_ns) {return 1;};
    unsigned long next_ts_for_update() {return 1;};

};



#endif
