/// G. Kosir adaption 
///Beam Monitor code merging to DESPEC. A.K.M, E.S. 
#include "Beam_Monitor_Detector_System.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
#include <climits>
#include "Riostream.h"

#include "TH1.h"
#include "TH2.h"
#include "TCutG.h"
#include "snprintf.h"

#include "TGo4MbsEvent.h"
#include "TGo4WinCond.h"
#include "TGo4PolyCond.h"
#include "TGo4CondArray.h"
#include "TGo4Picture.h"
#include "TGo4Fitter.h"
#include "TLatex.h"
#include "TFile.h"

#include <TRandom3.h>
using namespace std;
  std::string filename;
    char FileTime[80];
    char QFTime[80];


    double rate = 0;//5800 / ((pow(10, 8)));
    LongDouble_t S2sum_diff=0;
    LongDouble_t S4sum_diff=0;
    Int_t S2QFcount=0;
    Int_t S4QFcount=0;
    double QF;
    double K;

    const int MaxHits = 100000;
    const int doQFevery = 30000;

//     UIntArray S2TimeDiffs(MaxHits);
//     UIntArray S4TimeDiffs(MaxHits);
//     Long64_t S2Hits=0;
//     Long64_t S2AbsTimeStamp=0;
//     Long64_t S2AbsTimeStampPrev=0;  
//     Long64_t S4Hits=0;
//     Long64_t S4AbsTimeStamp=0;
//     Long64_t S4AbsTimeStampPrev=0;  
    
//     const Int_t NBinsMax = 100000; // bins for Hit times histogram
//     const Int_t NTimeMax = 10000; // in [ms]
//     
//     const Int_t NQFmax = 500;
//     const Int_t MaxTimeDiff= 100000;
//     
//     const Double_t dt_limit = 1000.0; // in [ms]
//     const Int_t MaxGraphPoints = 10000;
  


Beam_Monitor_Detector_System::Beam_Monitor_Detector_System(){
    l_evt_ct=0;
    l_phy_evt_ct=0;
    l_err_ct=0;
    
}
Beam_Monitor_Detector_System::~Beam_Monitor_Detector_System(){
}


void Beam_Monitor_Detector_System::Process_MBS(TGo4MbsSubEvent* psubevt)
{  // called by framework. We dont fill any output event here at all
    Beam_Monitor(psubevt);
}
  //fInput = (TGo4MbsEvent* ) GetInputEvent();
    void Beam_Monitor_Detector_System::Beam_Monitor(TGo4MbsSubEvent* psubevent){
        l_hit_ct_S2 = 0;
        l_hit_ct_S4 = 0;
        for(int i=0; i< BM_MAX_HITS; i++){
            l_diff_S2[i] = 0;
            l_diff_S4[i] = 0;
        }
//   if(fInput == 0)
//   {
//     std::cout << "AnlProc: no input event !"<< std::endl;
//     return kFALSE;
//   }
//   if(fInput->GetTrigger() > 11)
//   {
//     std::cout << "**** TSpillTimeStructProc: Skip trigger event"<< std::endl;
//     return kFALSE;
//   }
  // first we fill the arrays fCrate1,2 with data from MBS source
  // we have up to two subevents, crate 1 and 2
  // Note that one has to loop over all subevents and select them by
  // crate number:   psubevt->GetSubcrate(),
  // procid:         psubevt->GetProcid(),
  // and/or control: psubevt->GetControl()
  // here we use only crate number

  l_evt_ct++;
  l_phy_evt_ct++; // no difference up to now

  //fInput->ResetIterator();
  //while((psubevt = fInput->NextSubEvent()) != 0) // loop over subevents
  //{
    //printf ("next event \n"); fflush (stdout);
    psubevt = psubevent;
    
    
   // psubevt = fInput->NextSubEvent(); // only one subevent
    pl_se_dat = (uint32_t *)psubevt->GetDataField();
    pl_tmp = pl_se_dat;
    l_dat_len = psubevt->GetDlen();

    //sleep (1);

    // s2 
    for(int i=0; i<23; ++i) *pl_tmp++;

    l_head = *pl_tmp++;
    l_hit_ct = l_head & 0x1fff;
    l_id     = l_head & 0xffff0000;
   
//      printf("1 Header 0x%08x \n", l_head);
//      printf("1 Hit count 0x%08x \n", l_hit_ct);
//      printf("1 ID 0x%08x \n", l_id);
//      cout<<"psubevt->GetSubtype() " << psubevt->GetSubtype() << endl;
    
    if (l_id != 0xaaaa0000)
    {
      l_err_ct++;
      printf ("ERROR>> %d header not 0xaaaa0000 as expected \n", l_err_ct);
     // continue;

    }
    l_first = 1;
        l_hit_ct_S2 = l_hit_ct;
    for (l_i=0; l_i<l_hit_ct; l_i++) {
        
        l_hit_ti = *pl_tmp++;

        //std::cout << &pl_tmp << std::endl;
        //std::cout << l_hit_ti << std::endl;

        l_diff = l_hit_ti - l_pre_hit_ti;
        
        while(l_diff < 0) {
            l_diff = l_diff + UINT_MAX;
            if(l_diff > pow(10,8)) {
                l_diff = 0;
                l_diff_S2[l_i] = l_diff;
                ++l_i;
                }
            }
        if (l_first == 1){
            l_first = 0;
            }  
        else {
           // S2TimeDiffs[S2Hits%MaxHits] = l_diff/10.;
          ///  s2h_tdiff->Fill(l_diff);
            S2sum_diff+= (Long64_t) l_diff;// / 100000.0; // convert to miliseconds  
            l_diff_S2[l_i] = l_diff;
           // ++S2Hits;
            }
           
//              
//         S2AbsTimeStamp = ((Long64_t) ( S2sum_diff)) % ((Long64_t) NTimeMax*100000);
//         if(S2AbsTimeStamp < S2AbsTimeStampPrev) {
//                     TSpillTimeStructProc::BeamSpillAnalysis(s2h_t1, s2h_n);
//                     s2h_t1->Reset("ICESM");
//                     }
//         
//         
//         if(S2Hits>MaxHits && S2Hits%doQFevery==0){
//             s2h_tdiff->Reset("ICESM");
//             LongDouble_t timesum=0;
//             Int_t relevanthits=0;
//             for(Int_t k=0; k<MaxHits; ++k) {
//                 ///s2h_tdiff->Fill(S2TimeDiffs[k]);
//                 if(S2TimeDiffs[k] < dt_limit*pow(10,3)) {
//                     timesum+=S2TimeDiffs[k];
//                     ++relevanthits;
//                     }
//                 }
//             rate = (Double_t) relevanthits / timesum;
//             std::cout << "Rate: " << rate << std::endl;
//            /* TSpillTimeStructProc::NormTimeDiff(s2h_tdiff, s2h_norm_tdiff);
//             TSpillTimeStructProc::PoissonTimeDiff(s2h_poisson, rate);
//             TSpillTimeStructProc::CumulativePoisson(s2h_cp, s2h_poisson);
//             TSpillTimeStructProc::Cumulative(s2h_c, s2h_norm_tdiff, s2h_dc, s2h_cp);
//             S2QFcount = TSpillTimeStructProc::QualityFactor(s2h_poisson, s2h_norm_tdiff, s2h_dc, s2gr_qf, s2gr_dt_avrg, s2gr_dcmin, s2gr_dctime, S2QFcount);*/
//             }
//         
//         
//                 
//        /// s2h_t1->Fill( (Double_t) S2AbsTimeStamp*pow(10,-5));
//         
//         S2AbsTimeStampPrev = S2AbsTimeStamp;
         l_pre_hit_ti = l_hit_ti;
        }

    // s4
    l_head = *pl_tmp++;
    l_hit_ct = l_head & 0x1fff;
    l_id     = l_head & 0xffff0000;
    
//       printf("2 Header 0x%08x \n", l_head);
//      printf("2 Hit count 0x%08x \n", l_hit_ct);
//      printf("2 ID 0x%08x ", l_id);
    if (l_id != 0xbbbb0000)
    {
      l_err_ct++;
      printf ("ERROR>> %d header not 0xbbbb0000 as expected \n", l_err_ct);
     // return kTRUE;
    }
    l_first = 1;
            l_hit_ct_S4 = l_hit_ct;
    for (l_i=0; l_i<l_hit_ct; l_i++) {
        
        l_hit_ti = *pl_tmp++;
        l_diff = l_hit_ti - l_pre_hit_ti;
        
        if(l_diff < 0) {
            l_diff = l_diff + UINT_MAX;
            if(l_diff > pow(10,8)) {
                l_diff = 0;
                l_diff_S2[l_i] = l_diff;
                ++l_i;
                }
            }
        if (l_first == 1){
            l_first = 0;
            }  
        else {
         //   S4TimeDiffs[S4Hits%MaxHits] = l_diff/10;
        ///    s4h_tdiff->Fill(l_diff);
            S4sum_diff+= (Long64_t) l_diff;
            l_diff_S4[l_i] = l_diff;
         //   cout<<"l_diff " << l_diff_S4[l_i] << " l_hit_ct_S4 " <<l_hit_ct_S4 << endl;

           // ++S4Hits;
            }
             
//         S4AbsTimeStamp = ((Long64_t) ( S4sum_diff)) % ((Long64_t) NTimeMax*100000);
//         if(S4AbsTimeStamp < S4AbsTimeStampPrev) {
//                    // TSpillTimeStructProc::BeamSpillAnalysis(s4h_t1, s4h_n);
//                    // s4h_t1->Reset("ICESM");
//                     }
        
        
//         if(S4Hits>MaxHits && S4Hits%doQFevery==0){
//            // s4h_tdiff->Reset("ICESM");
//             LongDouble_t timesum=0;
//             Int_t relevanthits=0;
//             for(Int_t k=0; k<MaxHits; ++k) {
//             ///    s4h_tdiff->Fill(S4TimeDiffs[k]);
//                 if(S4TimeDiffs[k] < dt_limit*pow(10,3)) {
//                     timesum+=S4TimeDiffs[k];
//                     ++relevanthits;
//                     }
//                 }
//             rate = (Double_t) relevanthits / timesum;
//             std::cout << "Rate: " << rate << std::endl;
// //             NormTimeDiff(s4h_tdiff, s4h_norm_tdiff);
// //             TSpillTimeStructProc::PoissonTimeDiff(s4h_poisson, rate);
// //             TSpillTimeStructProc::CumulativePoisson(s4h_cp, s4h_poisson);
// //             TSpillTimeStructProc::Cumulative(s4h_c, s4h_norm_tdiff, s4h_dc, s4h_cp);
// //             S4QFcount = TSpillTimeStructProc::QualityFactor(s4h_poisson, s4h_norm_tdiff, s4h_dc, s4gr_qf, s4gr_dt_avrg, s4gr_dcmin, s4gr_dctime, S4QFcount);
//             }
        
        
                
      ///  s4h_t1->Fill( (Double_t) S4AbsTimeStamp*pow(10,-5)); 
        
        //S4AbsTimeStampPrev = S4AbsTimeStamp;
        l_pre_hit_ti = l_hit_ti;
        }
        
        
        
    l_head = *pl_tmp++;
    l_id     = l_head & 0xffff0000;
    if (l_id != 0xcccc0000)
    {
      l_err_ct++;
      printf ("ERROR>> %d trailer not 0xcccc0000 as expected \n", l_err_ct);
      //return kTRUE;
    }

    fflush (stdout);
    //return kTRUE;
}
void Beam_Monitor_Detector_System::get_Event_data(Raw_Event* RAW){

    RAW->set_DATA_Beam_Monitor(l_diff_S2,l_hit_ct_S2,l_diff_S4,l_hit_ct_S4);
}
int* Beam_Monitor_Detector_System::get_pdata(){return pdata;}