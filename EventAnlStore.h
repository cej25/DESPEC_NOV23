// $Id: EventAnlStore.h 755 2011-05-20 08:04:11Z linev $
// Adapted for DESPEC by A.K.Mistry 2020
//-----------------------------------------------------------------------
//       The GSI Online Offline Object Oriented (Go4) Project
//         Experiment Data Processing at EE department, GSI
//-----------------------------------------------------------------------
// Copyright (C) 2000- GSI Helmholtzzentrum f�r Schwerionenforschung GmbH
//                     Planckstr. 1, 64291 Darmstadt, Germany
// Contact:            http://go4.gsi.de
//-----------------------------------------------------------------------
// This software can be used under the license agreements as stated
// in Go4License.txt file which is part of the distribution.
//-----------------------------------------------------------------------

#ifndef TSCNCALEVENT_H
#define TSCNCALEVENT_H

#include "TGo4EventElement.h"
//#include "TSCNUnpackEvent.h"
#include "EventUnpackStore.h"
#include "AIDA_Event.h"
#include "BB7_TWINPEAKS_Event_Store.h"
#include "Configuration_Files/DESPEC_General_Setup/DESPEC_Setup_File.h"

struct AidaAnlData {
      std::vector<AidaHit> Implants;
      std::vector<AidaHit> Decays;
      };

struct BB7_FEBEX_AnlData
{
      std::vector<BB7_FEBEX_Hit> Implants;
      std::vector<BB7_FEBEX_Hit> Decays;
};

struct BB7_TWINPEAKS_AnlData
{
      std::vector<BB7_TWINPEAKS_Hit> Implants;
      std::vector<BB7_TWINPEAKS_Hit> Decays;
};

class EventAnlStore : public TGo4EventElement {
   public:
      EventAnlStore() : TGo4EventElement() {}
      EventAnlStore(const char* name) : TGo4EventElement(name) {}
      virtual ~EventAnlStore() {}

      virtual void  Clear(Option_t *t="");

      ///General Outputs
      Int_t pTrigger;
      Int_t pEvent_Number;
      Int_t pPrcID_Conv[7];
      bool pOnSpill;

      ///White Rabbit Outputs
      Long64_t pFRS_WR;
      Long64_t pbPLAS_WR;
      Long64_t pFAT_WR;
      Long64_t pFAT_Tamex_WR;
      Long64_t pAIDA_WR;
      Long64_t pGe_WR;
      Long64_t pBB7_FEBEX_WR;
      Long64_t pBB7_TWINPEAKS_WR;
      Long64_t pBB7_MADC_WR;
      ///FRS Outputs

      Float_t pFRS_AoQ;
      Float_t pFRS_ID_x2, pFRS_ID_y2, pFRS_ID_a2, pFRS_ID_b2;
      Float_t pFRS_ID_x4, pFRS_ID_y4, pFRS_ID_a4, pFRS_ID_b4;
      Float_t pFRS_z;
      Float_t pFRS_z2;
      Float_t pFRS_dEdeg;
      Float_t pFRS_dEdegoQ;
      Float_t pFRS_beta;
      Float_t pFRS_Music_dE[2];

      Float_t pFRS_AoQ_mhtdc[10];
      Float_t pFRS_z_mhtdc[10];      
      Float_t pFRS_z2_mhtdc[10];
      Float_t pFRS_beta_mhtdc[10];
      Float_t pFRS_dEdeg_mhtdc[10];
      Float_t pFRS_dEdegoQ_mhtdc[10];

      Float_t pFRS_sci_l[12];
      Float_t pFRS_sci_r[12];
      Float_t pFRS_sci_e[12];
      Float_t pFRS_sci_tx[12];
      Float_t pFRS_sci_x[12];
      Float_t pFRS_tpc_x[7];
      Float_t pFRS_tpc_y[7];
      UInt_t pFRS_scaler[64];
      UInt_t pFRS_scaler_delta[64];

      Double_t pTRaw_vftx_21l[VFTX_MAX_HITS];
      Double_t pTRaw_vftx_21r[VFTX_MAX_HITS];
      Double_t pTRaw_vftx_22l[VFTX_MAX_HITS];
      Double_t pTRaw_vftx_22r[VFTX_MAX_HITS];
      Double_t pTRaw_vftx_41l[VFTX_MAX_HITS];
      Double_t pTRaw_vftx_41r[VFTX_MAX_HITS];
      Double_t pTRaw_vftx_42l[VFTX_MAX_HITS];
      Double_t pTRaw_vftx_42r[VFTX_MAX_HITS];
      
      Float_t pbeta_vftx_2141[VFTX_MAX_HITS] , pgamma_vftx_2141[VFTX_MAX_HITS] , paoq_vftx_2141[VFTX_MAX_HITS] , paoq_corr_vftx_2141[VFTX_MAX_HITS], pz1_vftx_2141[VFTX_MAX_HITS],pz2_vftx_2141[VFTX_MAX_HITS] , pvcor_vftx_2141[VFTX_MAX_HITS];
   
      Float_t pbeta_vftx_2241[VFTX_MAX_HITS] , pgamma_vftx_2241[VFTX_MAX_HITS] , paoq_vftx_2241[VFTX_MAX_HITS] , paoq_corr_vftx_2241[VFTX_MAX_HITS], pz1_vftx_2241[VFTX_MAX_HITS],pz2_vftx_2241[VFTX_MAX_HITS] , pvcor_vftx_2241[VFTX_MAX_HITS];

      Bool_t pFRS_ZAoQ_pass[MAX_FRS_GATE];
      Bool_t pFRS_ZAoQ_pass_mhtdc[MAX_FRS_GATE];
      Bool_t pFRS_x2AoQ_pass[MAX_FRS_GATE];
      Bool_t pFRS_x2AoQ_pass_mhtdc[MAX_FRS_GATE];
      Bool_t pFRS_x4AoQ_pass[MAX_FRS_GATE];
      Bool_t pFRS_x4AoQ_pass_mhtdc[MAX_FRS_GATE];
      Bool_t pFRS_Z_Z2_pass[MAX_FRS_GATE];
      Bool_t pFRS_dEdegZ1_pass[MAX_FRS_GATE];
      Bool_t pFRS_dEdegZ1_pass_mhtdc[MAX_FRS_GATE];
      Bool_t pFRS_Z_Z2_pass_mhtdc[MAX_FRS_GATE];

      //Helena
      Long64_t pt_lastSC41 = 0;
      Long64_t pt_lastIMP_DSSD1 = 0;
      Long64_t pt_lastIMP_DSSD2 = 0;
      Long64_t pt_lastIMP_DSSD3 = 0;
      Float_t plastIMP_DSSD1_StripX = .0;
      Float_t plastIMP_DSSD2_StripX = .0;
      Float_t plastIMP_DSSD3_StripX = .0;

      
      std::vector<BB7_FEBEX_AnlData> pBB7_FEBEX;
      std::vector<BB7_TWINPEAKS_UnpackData> pBB7_TWINPEAKS_Unp;
      std::vector<BB7_TWINPEAKS_AnlData> pBB7_TWINPEAKS;

     ///AIDA output
       //AidaAnlData pAida;
      std::vector<AidaAnlData> pAida;
      std::vector<AidaScaler> pAidaScalers;

      Int_t         pFat_QDC_ID[FAT_VME_MAX_MULTI];
      Double_t      pFat_QDC_E[FAT_VME_MAX_MULTI];
      Double_t      pFat_QDC_E_Raw[FAT_VME_MAX_MULTI];
      Long64_t      pFat_QDC_T_coarse[FAT_VME_MAX_MULTI];
      Double_t      pFat_QDC_T_fine[FAT_VME_MAX_MULTI];
      Int_t         pFat_TDC_ID[FAT_VME_MAX_MULTI];
      Long64_t      pFat_TDC_T[FAT_VME_MAX_MULTI];
      Long64_t      pFat_TDC_T_Raw[FAT_VME_MAX_MULTI];

      Int_t         pFatmult;
      Int_t         pSC40mult;
      Int_t         pSC41mult;

      Int_t pFat_TDC_Singles_ID[FAT_VME_MAX_MULTI];
      Long64_t pFat_TDC_Singles_t[FAT_VME_MAX_MULTI];
      Long64_t pFat_TDC_Singles_t_Raw[FAT_VME_MAX_MULTI];
      Long64_t pFat_QDC_Singles_t_coarse[FAT_VME_MAX_MULTI];
      double_t pFat_QDC_Singles_t_fine[FAT_VME_MAX_MULTI];

      Int_t pFat_QDC_Singles_ID[FAT_VME_MAX_MULTI];
      Double_t pFat_QDC_Singles_E[FAT_VME_MAX_MULTI];
      Double_t pFat_QDC_Singles_E_Raw[FAT_VME_MAX_MULTI];
      UInt_t pstdcmult;
      UInt_t psqdcmult;

      //SC 40 and 41 arrays
      Long64_t pSC40[10];
      Long64_t pSC41[10];
      Long64_t pFat_TMCh1[10];
      Long64_t pFat_TMCh2[10];
      Int_t    pFat_TMCh1mult;
      Int_t    pFat_TMCh2mult;

      double_t pFat_bplastChanT[6];
//       Int_t    pSC40mult;
//       Int_t    pSC41mult;


      Double_t pFat_Fast_ToTCalib[FATIMA_TAMEX_CHANNELS][FATIMA_TAMEX_HITS];
      Double_t pFat_Slow_ToTCalib[FATIMA_TAMEX_CHANNELS][FATIMA_TAMEX_HITS];
      Double_t pFat_Fast_LeadT[FATIMA_TAMEX_CHANNELS][FATIMA_TAMEX_HITS];
      Double_t pFat_Slow_LeadT[FATIMA_TAMEX_CHANNELS][FATIMA_TAMEX_HITS];
      Double_t pFat_Fast_TrailT[FATIMA_TAMEX_CHANNELS][FATIMA_TAMEX_HITS];
      Double_t pFat_Slow_TrailT[FATIMA_TAMEX_CHANNELS][FATIMA_TAMEX_HITS];
      Int_t    pFat_LeadHits;
     // Int_t    pFat_TrailHits;
      Int_t    pFat_Tamex_chan[FATIMA_TAMEX_HITS];

//       Int_t    pbPlasDetNum;
//       Int_t    pbPlasChan[4];
//       Double_t pbPlas_ToTCalib[4][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
//       Int_t    pbPlas_PMT_Lead_N[4][bPLASTIC_CHAN_PER_DET];
//       Double_t pbPlas_LeadT[4][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
//       Double_t pbPlas_LeadT_Avg;
//       Int_t    pbPlas_PMT_Trail_N[4][bPLASTIC_CHAN_PER_DET];
//       Double_t pbPlas_TrailT[4][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
//       Int_t    pbPlas_LeadHits;
//       Int_t    pbPlas_TrailHits;

      Int_t pbPlasDetNum_Fast;
      Int_t pbPlasDetNum_Slow;
      Int_t pbPlas_FastChan[bPLASTIC_TAMEX_MODULES];
      Int_t pbPlas_SlowChan[bPLASTIC_TAMEX_MODULES];
      Int_t pbPlas_Fast_Lead_N[bPLASTIC_TAMEX_MODULES][bPLASTIC_CHAN_PER_DET];
      Int_t pbPlas_Slow_Lead_N[bPLASTIC_TAMEX_MODULES][bPLASTIC_CHAN_PER_DET];
      Double_t pbPlas_FastLeadT[bPLASTIC_TAMEX_MODULES][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
      Double_t pbPlas_SlowLeadT[bPLASTIC_TAMEX_MODULES][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
      Int_t pbPlas_FastLeadHits;
      Int_t pbPlas_SlowLeadHits;
      Int_t pbPlast_Fast_Trail_N[bPLASTIC_TAMEX_MODULES][bPLASTIC_CHAN_PER_DET];
      Int_t pbPlast_Slow_Trail_N[bPLASTIC_TAMEX_MODULES][bPLASTIC_CHAN_PER_DET];
      Double_t pbPlas_Fast_TrailT[bPLASTIC_TAMEX_MODULES][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
      Double_t pbPlas_Slow_TrailT[bPLASTIC_TAMEX_MODULES][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
      Double_t pbPlas_Fast_ToTCalib[bPLASTIC_TAMEX_MODULES][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
      Double_t pbPlas_Slow_ToTCalib[bPLASTIC_TAMEX_MODULES][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];

      // BB7 output
      Int_t pBB7_TWINPEAKS_FastStrip[BB7_SIDES];
      Int_t pBB7_TWINPEAKS_SlowStrip[BB7_SIDES];
      Int_t pBB7_TWINPEAKS_Fast_Lead_N[BB7_SIDES][BB7_STRIPS_PER_SIDE];
      Double_t pBB7_TWINPEAKS_FastLeadT[BB7_SIDES][BB7_STRIPS_PER_SIDE][BB7_TAMEX_MAX_HITS];
      Int_t pBB7_TWINPEAKS_FastLeadHits;
      Int_t pBB7_TWINPEAKS_Fast_Trail_N[BB7_SIDES][BB7_STRIPS_PER_SIDE];
      Int_t pBB7_TWINPEAKS_Slow_Trail_N[BB7_SIDES][BB7_STRIPS_PER_SIDE];
      Double_t pBB7_TWINPEAKS_Fast_TrailT[BB7_SIDES][BB7_STRIPS_PER_SIDE][BB7_TAMEX_MAX_HITS];
      Double_t pBB7_TWINPEAKS_Slow_TrailT[BB7_SIDES][BB7_STRIPS_PER_SIDE][BB7_TAMEX_MAX_HITS];
      Double_t pBB7_TWINPEAKS_Fast_ToTCalib[BB7_SIDES][BB7_STRIPS_PER_SIDE][BB7_TAMEX_MAX_HITS];
      Double_t pBB7_TWINPEAKS_Slow_ToTCalib[BB7_SIDES][BB7_STRIPS_PER_SIDE][BB7_TAMEX_MAX_HITS];
      Int_t pBB7_TWINPEAKS_Slow_Lead_N[BB7_SIDES][BB7_STRIPS_PER_SIDE];
      Double_t pBB7_TWINPEAKS_SlowLeadT[BB7_SIDES][BB7_STRIPS_PER_SIDE][BB7_TAMEX_MAX_HITS];
      Int_t pBB7_TWINPEAKS_SlowLeadHits;

          ULong64_t pGe_Event_T[Germanium_MAX_DETS][Germanium_CRYSTALS];
          ULong64_t pGe_T[Germanium_MAX_DETS][Germanium_CRYSTALS];
          ULong64_t pGe_T_Aligned[Germanium_MAX_DETS][Germanium_CRYSTALS];
          ULong64_t pGe_CF_T[Germanium_MAX_DETS][Germanium_CRYSTALS];
          ULong64_t pGe_CF_T_Aligned[Germanium_MAX_DETS][Germanium_CRYSTALS];
          double   pGe_E[Germanium_MAX_DETS][Germanium_CRYSTALS];
          double   pGe_E_Raw[Germanium_MAX_DETS][Germanium_CRYSTALS];
          double   pGe_EAddback[Germanium_MAX_DETS][Germanium_CRYSTALS];
          bool     pGePileUp[Germanium_MAX_HITS];
          bool     pGeOverFlow[Germanium_MAX_HITS];



//       Int_t pFing_tot;
//     //  Double_t pFing_lead_lead[52];
//       Double_t pFing_Lead_Up[52][100];
//       Double_t pFing_Lead_Down[52][100];
//       Double_t pFing_Trail_Up[52][100];
//       Double_t pFing_Trail_Down[52][100];
//       Int_t pFing_stripID;
//       Double_t pFing_maxtot;
//       Int_t pFing_maxtotchan;

   ClassDef(EventAnlStore,1)
};
#endif //TSCNCALEVENT_H
