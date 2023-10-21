#ifndef BB7_TWINPEAKS_DETECTOR_SYSTEM_H
#define BB7_TWINPEAKS_DETECTOR_SYSTEM_H

#include <iostream>
#include <string>

#include "Detector_System.cxx"
#include "BB7_TAMEX_Calibrator.h"
#include "Raw_Event.h"

#include "TAMEX.h"
#define MAX_CHA_INPUT 33 // is this correct? trigger + 1-32 for fast/slow?

typedef unsigned long long ULong64_t;
typedef unsigned long ULong;

class BB7_TWINPEAKS_Detector_System : public Detector_System
{
    private:
        BB7_TAMEX_Calibrator* BB7_TAMEX_Calibration;

        bool tamex_end;
        bool no_edges[100];
        bool written;
        bool CALIBRATE, Calibration_Done;
        
        int cal_count;
        int* pdata;

        // used?
        int unknown;
        int increase;

        int am_fired[100];
        int sfp_id[100];
        int trigger_type[100];
        int* iterator;
        int tamex_id[100];

        int tamex_iter;
        
        ULong Pre_Trigger_Window;
        ULong Post_Trigger_Window;

        int** leading_hits;
        int** trailing_hits;
        int** lead_arr;

        Bool_t leading_hit;
        double** edge_coarse;
        double** edge_fine;
        unsigned int** ch_ID_edge;

        // why are these 100 x 100?
        unsigned int ch_ID_edge_lead[100][100];
        unsigned int ch_ID_edge_trail[100][100];
        
        double* coarse_T;
        double* fine_T;
        unsigned int* ch_ID;

        void check_error();
        void check_trailer();
        void get_edges();
        void get_trigger();
        void skip_padding();
        void Process_TAMEX();
        void calibrate_ONLINE();
        void calibrate_OFFLINE();

        void get_Calib_type();
        void reset_edges();

        bool no_error_reached();
    
    public:
        BB7_TWINPEAKS_Detector_System();
        ~BB7_TWINPEAKS_Detector_System();

        void Process_MBS(TGo4MbsSubEvent* psubevt) {};
        void Process_MBS(int*);

        void get_Event_data(Raw_Event*);

        int* get_pdata();

        bool calibration_done();

        void write() { return; }
        void set_Gain_Match_Filename(std::string) { return; }
        
        unsigned int epoch_data;

        bool do_gain_matching(int ts_ns) { return 1; }
        unsigned long next_ts_for_update() { return 1; } 

};

#endif