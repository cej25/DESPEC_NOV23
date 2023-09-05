//-------------------------------------------------------------
//        Go4 Release Package v3.03-05 (build 30305)
//                      05-June-2008
//---------------------------------------------------------------
//   The GSI Online Offline Object Oriented (Go4) Project
//   Experiment Data Processing at EE department, GSI
//---------------------------------------------------------------
//
//Copyright (C) 2000- Gesellschaft f. Schwerionenforschung, GSI
//                    Planckstr. 1, 64291 Darmstadt, Germany
//Contact:            http://go4.gsi.de
//----------------------------------------------------------------
//This software can be used under the license agreements as stated
//in Go4License.txt file which is part of the distribution.
//----------------------------------------------------------------
#ifndef BEAM_MONITOR_DETECTOR_SYSTEM_H
#define BEAM_MONITOR_DETECTOR_SYSTEM_H
#include "Beam_Monitor_Detector_System.h"

#include "Riostream.h"

#include "TH1.h"
#include "TMap.h"
#include "TObject.h"

#include <cstdlib>
#include <bitset>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>

// Go4 Includes //
#include "TGo4UserException.h"
#include "TGo4Picture.h"
#include "TGo4MbsEvent.h"
#include "TGo4StepFactory.h"
#include "TGo4Analysis.h"
#include "TGo4AnalysisObjectManager.h"
#include "TGo4WinCond.h"
#include "TGo4AnalysisObjectManager.h"
#include "TGo4EventProcessor.h"
#include "DESPECAnalysis.h"
#include "TFRSParameter.h"
#include "Go4StatusBase/TGo4Parameter.h"

#include "Detector_System.cxx"

#include <sys/stat.h>
#include <sys/types.h>
#include <TRandom3.h>
#include <valarray>
#include <climits>
typedef std::valarray<UInt_t>  UIntArray;

///typedef std::valarray<UInt_t>  UIntArray;

// char QFTime[80];
// 
// 
//     double rate ;//5800 / ((pow(10, 8)));
//     LongDouble_t S2sum_diff;
//     LongDouble_t S4sum_diff;
//     Int_t S2QFcount;
//     Int_t S4QFcount;
//     double QF;
//     double K;
// 
// 
    // const int MaxHits ;
//     const int doQFevery;
// 
   //  UIntArray S2TimeDiffs(MaxHits);
//     UIntArray S4TimeDiffs(MaxHits);
//     Long64_t S2Hits;
//     Long64_t S2AbsTimeStamp;
//     Long64_t S2AbsTimeStampPrev;  
//     Long64_t S4Hits;
//     Long64_t S4AbsTimeStamp;
//     Long64_t S4AbsTimeStampPrev;  
//     
//     const Int_t NBinsMax ; // bins for Hit times histogram
//     const Int_t NTimeMax ; // in [ms]
//     
//     
//     
//     const Int_t NQFmax ;
//     const Int_t MaxTimeDiff;
//     
//     const Double_t dt_limit ; // in [ms]
//     const Int_t MaxGraphPoints ;
    
/// class TSpillTimeStructParam;
/// class TGo4Fitter;

class Beam_Monitor_Detector_System : public Detector_System{
   public:
      Beam_Monitor_Detector_System() ;
      void Process_MBS(TGo4MbsSubEvent* psubevt);
      
      virtual ~Beam_Monitor_Detector_System();
     // TSpillTimeStructProc(const char* name);
     // virtual ~TSpillTimeStructProc() ;
      
       void Process_MBS(int*){};
        void get_Event_data(Raw_Event*);
        int* get_pdata();
       private:
          
           
           TGo4MbsSubEvent* psubevt;
              Int_t *pdata;
           
             Int_t      l_i;
             uint32_t  *pl_se_dat;
             uint32_t  *pl_tmp;

            UInt_t     l_dat_len;  

             ULong64_t  l_evt_ct=0;
             ULong64_t  l_phy_evt_ct=0;

             UInt_t    l_first;
             UInt_t    l_head;
             UInt_t    l_hit_ct;
             UInt_t    l_id;
             UInt_t    l_hit_ti;
             Long64_t    l_diff;
             UInt_t    l_pre_hit_ti;
             UInt_t    l_err_ct=0;
             
             UInt_t l_hit_ct_S2;
             UInt_t l_hit_ct_S4;
             
             Long64_t l_diff_S2[BM_MAX_HITS];
             Long64_t l_diff_S4[BM_MAX_HITS];
            
            void Beam_Monitor(TGo4MbsSubEvent* psubevt);

   //   Bool_t BuildEvent(TGo4EventElement* target); // event processing function
    
    
//     void BeamSpillAnalysis(TH1* h_t1, TH1* h_n);
//     Int_t QualityFactor(TH1* h_poisson, TH1* h_norm_tdiff, TH1* h_dc, TGraph* gr_qf, TGraph* gr_dt_avrg, TGraph* gr_dcmin, TGraph* gr_dctime, Int_t QFcount);
//     void PoissonTimeDiff(TH1* h_poisson, Double_t rate);
//     void Cumulative(TH1* h_c, TH1* h_norm_tdiff, TH1* h_dc, TH1* h_cp);
//     void CumulativePoisson(TH1* h_cp, TH1* h_poisson);
//     void NormTimeDiff(TH1* h_tdiff, TH1* h_norm_tdiff);
    
      // Useless but needed for Detector_System
    bool calibration_done(){return false;}
    void write(){return;};
    void set_Gain_Match_Filename(std::string){return;};
    bool do_gain_matching(int ts_ns) {return 1;};
    unsigned long next_ts_for_update() {return 1;};
    
};

#endif