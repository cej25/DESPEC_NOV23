#ifndef RAW_EVENT_H
#define RAW_EVENT_H

#include <math.h>
#include <float.h>
#include <vector>

#include "AIDA_Event.h"
#include "AIDA_Decay_Event_Store.h"
#include "Configuration_Files/DESPEC_General_Setup/DESPEC_Setup_File.h"

// KW add
#include "TFRSVftxSetting.h"
// end KW
//#include "Rtypes.h"

typedef unsigned long ULong;
typedef unsigned int UInt;
typedef unsigned long long ULong64_t;
typedef float Float_t;
typedef int Int_t;


class Raw_Event{

private:


	// ##########################################################

	//FRS
	// MUSIC PARAMETERS //

	Float_t MUSIC_dE[3];      // set_DATA_MUSIC
	Float_t MUSIC_dE_cor[3];  // set_DATA_MUSIC
	Float_t MUSIC_e1[8]; // set_DATA_MUSIC
	Float_t MUSIC_e2[8]; // set_DATA_MUSIC
	Float_t MUSIC_t1[8]; // set_DATA_MUSIC
    Float_t MUSIC_t2[8]; // set_DATA_MUSIC
	// SCINTILLATOR PARAMETERS //

	Float_t sci_l[12];  // set_DATA_SCI
	Float_t sci_r[12];  // set_DATA_SCI
	Float_t sci_e[12];  // set_DATA_SCI
	Float_t sci_tx[12]; // set_DATA_SCI
	Float_t sci_x[12];  // set_DATA_SCI



	Int_t dt_21l_21r;
	Int_t dt_41l_41r;
	Int_t dt_21l_41l;
	Int_t dt_21r_41r;
	Int_t dt_42l_42r;
	Int_t dt_43l_43r;
	Int_t dt_21l_42l;
	Int_t dt_21r_42r;
	Int_t dt_81l_81r;
	Int_t dt_21l_81l;
	Int_t dt_21r_81r;


	Float_t sci_tofll2; // set_DATA_SCI_ToF
	Float_t sci_tofll3; // set_DATA_SCI_ToF
	Float_t sci_tofll5; // set_DATA_SCI_ToF
	Float_t sci_tofrr2; // set_DATA_SCI_ToF
	Float_t sci_tofrr3; // set_DATA_SCI_ToF
	Float_t sci_tofrr5;
	Float_t sci_tof2;   // set_DATA_SCI_ToF
	Float_t sci_tof3;   // set_DATA_SCI_ToF
	Float_t sci_tof5;   // set_DATA_SCI_ToF
	Float_t sci_tof2_calib;   // set_DATA_SCI_ToF
	Float_t sci_tof3_calib;   // set_DATA_SCI_ToF
	Float_t sci_tof5_calib;   // set_DATA_SCI_ToF

	// ID PARAMETERS //

	Float_t ID_x2;      // set_DATA_ID_2_4
	Float_t ID_y2;      // set_DATA_ID_2_4
	Float_t ID_a2;      // set_DATA_ID_2_4
	Float_t ID_b2;      // set_DATA_ID_2_4

	Float_t ID_x4;      // set_DATA_ID_2_4
	Float_t ID_y4;      // set_DATA_ID_2_4
	Float_t ID_a4;      // set_DATA_ID_2_4
	Float_t ID_b4;      // set_DATA_ID_2_4
// TPC part 7 TPCs each one with 2 delay lines each!!
  //7 TPCs (4 at S2, 2 at S4 and one at S3) 03.07.2018 SB
  //ADCs
  Int_t TPC_l[7][2]; //[i_tpc][i_delayline_L]
  Int_t TPC_r[7][2]; //[i_tpc][i_delayline_R]
  Int_t TPC_a[7][4]; //[i_tpc][i_anode]
	Float_t TPC_x[7];
    Float_t TPC_y[7];
    Int_t   TPC_lt[7][2][64];
    Int_t   TPC_rt[7][2][64];
    Int_t   TPC_dt[7][4][64];
    Float_t TPC_x_s2_foc_23_24;
    Float_t TPC_y_s2_foc_23_24;
    Float_t TPC_x_angle_s2_foc_23_24;
    Float_t TPC_y_angle_s2_foc_23_24;
    Float_t TPC23_24_x_sc21;
    Float_t TPC23_24_y_sc21;
    Float_t TPC23_24_x_sc22;
    Float_t TPC23_24_y_sc22;
    Float_t TPC_x_s4;
    Float_t TPC_y_s4;
    Float_t TPC_x_angle_s4;
    Float_t TPC_y_angle_s4;
    Float_t TPC_x_sc41, TPC_y_sc41, TPC_x_sc42,TPC_y_sc42;
    
	Float_t ID_brho[2]; // set_DATA_ID_Beta_Rho
	Float_t ID_rho[2];  // set_DATA_ID_Beta_Rho

	Float_t beta;       // set_DATA_ID_Beta_Rho
	Float_t beta3;      // set_DATA_ID_Beta_Rho
	Float_t gamma;      // set_DATA_ID_Beta_Rho

	Float_t AoQ;        // set_DATA_ID_Z_AoQ
	Float_t AoQ_corr;   // set_DATA_ID_Z_AoQ

	Float_t z;          // set_DATA_ID_Z_AoQ
	Float_t z2;         // set_DATA_ID_Z_AoQ
	Float_t z3;         // set_DATA_ID_Z_AoQ

	Float_t dEdeg;         // set_DATA_ID_Z_AoQ
    Float_t dEdegoQ;         // set_DATA_ID_Z_AoQ

	Float_t timestamp;  // set_DATA_ID_Timestamp
	Float_t ts;         // set_DATA_ID_Timestamp
	Float_t ts2;        // set_DATA_ID_Timestamp

	Int_t   time_in_ms;
    Int_t   spill_count;
    Int_t   ibin_for_s;
    Int_t   ibin_for_100ms;
    Int_t   ibin_for_spill;
    Int_t   ibin_clean_for_s;
    Int_t   ibin_clean_for_100ms;
    Int_t   ibin_clean_for_spill;
    UInt_t  increase_scaler_temp[64];

  //KW changed [32] to [VFTX_MAX_HITS] because, why not?
    Double_t TRaw_vftx_21L[VFTX_MAX_HITS];
    Double_t TRaw_vftx_21R[VFTX_MAX_HITS];
    Double_t TRaw_vftx_22L[VFTX_MAX_HITS];
    Double_t TRaw_vftx_22R[VFTX_MAX_HITS];
    Double_t TRaw_vftx_41L[VFTX_MAX_HITS];
    Double_t TRaw_vftx_41R[VFTX_MAX_HITS];
    Double_t TRaw_vftx_42L[VFTX_MAX_HITS];
    Double_t TRaw_vftx_42R[VFTX_MAX_HITS];
    Float_t ToF_vftx_2141[VFTX_MAX_HITS];
    Float_t ToF_vftx_2141_calib[VFTX_MAX_HITS];
    Float_t ToF_vftx_2241[VFTX_MAX_HITS];
    Float_t ToF_vftx_2241_calib[VFTX_MAX_HITS];
  // KW add
  Float_t ToF_vftx_2142[VFTX_MAX_HITS];
  Float_t ToF_vftx_2142_calib[VFTX_MAX_HITS];
  Float_t ToF_vftx_2242[VFTX_MAX_HITS];
  Float_t ToF_vftx_2242_calib[VFTX_MAX_HITS];

  Float_t ID_vftx_aoq_2141[VFTX_MAX_HITS];
  Float_t ID_vftx_aoq_corr_2141[VFTX_MAX_HITS];
  Float_t ID_vftx_z_2141[VFTX_MAX_HITS];
  Float_t ID_vftx_z2_2141[VFTX_MAX_HITS];
  Float_t ID_vftx_beta_2141[VFTX_MAX_HITS];

  Float_t ID_vftx_aoq_2241[VFTX_MAX_HITS];
  Float_t ID_vftx_aoq_corr_2241[VFTX_MAX_HITS];
  Float_t ID_vftx_z_2241[VFTX_MAX_HITS];
  Float_t ID_vftx_z2_2241[VFTX_MAX_HITS];
  Float_t ID_vftx_beta_2241[VFTX_MAX_HITS];

  Float_t ID_vftx_aoq_2142[VFTX_MAX_HITS];
  Float_t ID_vftx_aoq_corr_2142[VFTX_MAX_HITS];
  Float_t ID_vftx_z_2142[VFTX_MAX_HITS];
  Float_t ID_vftx_z2_2142[VFTX_MAX_HITS];
  Float_t ID_vftx_beta_2142[VFTX_MAX_HITS];

  Float_t ID_vftx_aoq_2242[VFTX_MAX_HITS];
  Float_t ID_vftx_aoq_corr_2242[VFTX_MAX_HITS];
  Float_t ID_vftx_z_2242[VFTX_MAX_HITS];
  Float_t ID_vftx_z2_2242[VFTX_MAX_HITS];
  Float_t ID_vftx_beta_2242[VFTX_MAX_HITS];
  
  // end KW
    Float_t Raw_mhtdc_sc21lr_dt[10];
    Float_t Raw_mhtdc_sc21lr_x[10];
    Float_t Raw_mhtdc_sc22lr_dt[10];
    Float_t Raw_mhtdc_sc22lr_x[10];
    Float_t Raw_mhtdc_sc41lr_dt;
    Float_t Raw_mhtdc_sc41lr_x;
    Float_t Raw_mhtdc_sc42lr_dt;
    Float_t Raw_mhtdc_sc42lr_x;

    Float_t ID_mhtdc_AoQ[10];
    Float_t ID_mhtdc_AoQ_corr[10];
    Float_t ID_mhtdc_Z1[10];
    Float_t ID_mhtdc_Z2[10];
    Float_t ID_mhtdc_dEdeg[10];
    Float_t ID_mhtdc_dEdegoQ[10];
    Float_t ID_mhtdc_Beta[10];
    Float_t ID_mhtdc_tof4221;
    Float_t ID_mhtdc_tof4121[10];
    Float_t ID_mhtdc_tof4122[10];
	// ##########################################################

	//White Rabbit
	ULong64_t WR;

    //AIDA
    double      AIDA_Energy[AIDA_MAX_HITS];
    int         AIDA_FEE[AIDA_MAX_HITS];
    int         AIDA_CHA_ID[AIDA_MAX_HITS];
    ULong64_t   AIDA_WR[AIDA_MAX_HITS];
    int         AIDA_Hits;
    bool        AIDA_HighE_VETO[AIDA_MAX_HITS];
    int         AIDA_SIDE[AIDA_MAX_HITS];
    int         AIDA_STRIP[AIDA_MAX_HITS];
    int         AIDA_EVT_ID[AIDA_MAX_HITS];
	ULong64_t   AIDA_FastTime[AIDA_MAX_HITS];
	int         AIDA_ADC[AIDA_MAX_HITS];
	std::vector<AidaScaler> AIDA_SCALERS;
	std::vector<AidaPauseResume> AIDA_PAUSERESUME;



//     double AIDA_DecayEnergy[12][64][2];
//     ULong64_t AIDA_DecayTimestamp[24][64];
//     int AIDA_DecayID[24];
//     int AIDA_DecayFEE;
//     int AIDA_Decayhits;
//
//     double AIDA_ImpEnergy[24][64];
//     ULong64_t AIDA_ImpTimestamp[24][64];
//     int AIDA_ImpID[24];
//     int AIDA_ImpFEE;
//     int AIDA_Imphits;

    int    FAT_DET_FIRED;         //number of completed detectors in evt
    int    FAT_id[100];           //id according to allocation file
    double FAT_E[100];            //energy (calibrated nad gain matched)
    double FAT_ratio[100];        //Qshort/Qlong
    double FAT_t[100];            //tdc time  (ns, shifted)
    double FAT_t_qdc[100];        //qdc time  (ns, shifted)
    //For trouble debugging:
    int    FAT_QDCs_FIRED;
    int    FAT_QDC_id[100];
    double FAT_QLong[100];        //calibrated
    double FAT_QLong_Raw[100];
    double FAT_QShort_Raw[100];
    ULong  FAT_QDC_t_coarse[100];
    double FAT_QDC_t_fine[100];  //qdc time (ns)
    //
    int    FAT_TDCs_FIRED;
    int    FAT_TDC_id[100];
    ULong64_t FAT_TDC_timestamp[100];//tdc time
    ULong64_t FAT_TDC_timestamp_raw[100];//tdc time
    // for vector array
	//FATIMA_DataStruct FATIMA_Data;

	//FATIMA TAMEX
    int     amount_hit_tamex_fat;
    int     iterator_fat[FATIMA_TAMEX_MODULES];
    double  trigger_coarse_fat[100];
    double  trigger_fine_fat[100];
    int     leading_array_fat[FATIMA_TAMEX_MODULES][100];
    int     leading_hits_fat[FATIMA_TAMEX_MODULES];
    int     trailing_hits_fat[FATIMA_TAMEX_MODULES];
    int     phys_channel_fat[FATIMA_TAMEX_MODULES][100];
    int     leading_hits_ch_fat[FATIMA_TAMEX_MODULES][100];
    int     trailing_hits_ch_fat[FATIMA_TAMEX_MODULES][100];
    UInt    ch_ID_fat[FATIMA_TAMEX_MODULES][100];
    double  coarse_T_edge_lead_fat[FATIMA_TAMEX_MODULES][100];
    double  coarse_T_edge_trail_fat[FATIMA_TAMEX_MODULES][100];
    double  fine_T_edge_lead_fat[FATIMA_TAMEX_MODULES][100];
    double  fine_T_edge_trail_fat[FATIMA_TAMEX_MODULES][100];
    bool    fired_tamex_fat[FATIMA_TAMEX_MODULES];
    UInt epoch_ch_leading[FATIMA_TAMEX_MODULES][100];
    UInt epoch_ch_trailing[FATIMA_TAMEX_MODULES][100];

	//bPlastic
//  	PLASTIC_DataStruct PLASTIC_Data;
//  	PLASTIC_VME_DataStruct PLASTIC_VME_Data;

    //FINGER
    int         amount_hit_tamex;
    int         iterator[FINGER_TAMEX_MODULES];
    double      trigger_coarse[FINGER_TAMEX_HITS];
    double      trigger_fine[FINGER_TAMEX_HITS];
    int         leading_array[FINGER_TAMEX_MODULES][FINGER_TAMEX_HITS];
    int         leading_hits[FINGER_TAMEX_MODULES];
    int         trailing_hits[FINGER_TAMEX_MODULES];
    int         phys_channel[FINGER_TAMEX_MODULES][FINGER_TAMEX_HITS];
    int         leading_hits_ch[FINGER_TAMEX_MODULES][FINGER_TAMEX_HITS];
    int         trailing_hits_ch[FINGER_TAMEX_MODULES][FINGER_TAMEX_HITS];
    UInt        ch_ID[FINGER_TAMEX_MODULES][FINGER_TAMEX_HITS];

    double      coarse_T_edge_lead[FINGER_TAMEX_MODULES][FINGER_TAMEX_HITS];
    double      coarse_T_edge_trail[FINGER_TAMEX_MODULES][FINGER_TAMEX_HITS];
    double      fine_T_edge_lead[FINGER_TAMEX_MODULES][FINGER_TAMEX_HITS];
    double      fine_T_edge_trail[FINGER_TAMEX_MODULES][FINGER_TAMEX_HITS];

    bool fired_tamex[4];

	bool VME_Event;

    //bPlastic VME
//     int         QDC_IT;
//     int         TDC_IT;
//     double      VME_QDC_DAT1[100];
//     double      VME_QDC_DAT2[100];
//     int         VME_QDC_CHA[100];
//     double      VME_TDC_DAT[50];
//     int         VME_TDC_CHA[50];
//
//     int         SCALER_ITERATOR;
//     double      SCALER_DATA[17];


    //bPlastic TAMEX
    int         amount_hit_tamex_bPlas;
    int         tamex_id_bPlas[100];
    int         iterator_bPlas[bPLASTIC_TAMEX_MODULES];
    double      trigger_coarse_bPlas[bPLASTIC_TAMEX_MODULES*bPLASTIC_TAMEX_CHANNELS];
    double      trigger_fine_bPlas[bPLASTIC_TAMEX_MODULES*bPLASTIC_TAMEX_CHANNELS];
    int         leading_array_bPlas[bPLASTIC_TAMEX_MODULES][bPLASTIC_TAMEX_MODULES*bPLASTIC_TAMEX_CHANNELS];
    int         leading_hits_bPlas[bPLASTIC_TAMEX_MODULES];
    int         trailing_hits_bPlas[bPLASTIC_TAMEX_MODULES];
    int         phys_channel_bPlas[bPLASTIC_TAMEX_MODULES][bPLASTIC_TAMEX_MODULES*bPLASTIC_TAMEX_CHANNELS];
    int         leading_hits_ch_bPlas[bPLASTIC_TAMEX_MODULES][bPLASTIC_TAMEX_MODULES*bPLASTIC_TAMEX_CHANNELS];
    int         trailing_hits_ch_bPlas[bPLASTIC_TAMEX_MODULES][bPLASTIC_TAMEX_MODULES*bPLASTIC_TAMEX_CHANNELS];
    int         ch_ID_bPlas[bPLASTIC_TAMEX_MODULES][100];
    double      coarse_T_edge_lead_bPlas[bPLASTIC_TAMEX_MODULES][bPLASTIC_TAMEX_MODULES*bPLASTIC_TAMEX_CHANNELS];
    double      coarse_T_edge_trail_bPlas[bPLASTIC_TAMEX_MODULES][bPLASTIC_TAMEX_MODULES*bPLASTIC_TAMEX_CHANNELS];
    double      fine_T_edge_lead_bPlas[bPLASTIC_TAMEX_MODULES][bPLASTIC_TAMEX_MODULES*bPLASTIC_TAMEX_CHANNELS];
    double      fine_T_edge_trail_bPlas[bPLASTIC_TAMEX_MODULES][bPLASTIC_TAMEX_MODULES*bPLASTIC_TAMEX_CHANNELS];
    double      lead_T_bPlas[bPLASTIC_TAMEX_MODULES][bPLASTIC_TAMEX_MODULES*bPLASTIC_TAMEX_CHANNELS];
    double      trail_T_bPlas[bPLASTIC_TAMEX_MODULES][bPLASTIC_TAMEX_MODULES*bPLASTIC_TAMEX_CHANNELS];
    double      ToT[bPLASTIC_TAMEX_MODULES][bPLASTIC_TAMEX_MODULES*bPLASTIC_TAMEX_CHANNELS];
    bool        fired_tamex_bPlas[bPLASTIC_TAMEX_MODULES];
    
     //bPlast Twinpeaks TAMEX
    int     amount_hit_bPlastTwinPeaks;
    int     iterator_bPlastTwinPeaks[bPLASTIC_TAMEX_MODULES];
    double  trigger_coarse_bPlastTwinPeaks[100];
    double  trigger_fine_bPlastTwinPeaks[100];
    int     leading_array_bPlastTwinPeaks[bPLASTIC_TAMEX_MODULES][100];
    int     leading_hits_bPlastTwinPeaks[bPLASTIC_TAMEX_MODULES];
    int     trailing_hits_bPlastTwinPeaks[bPLASTIC_TAMEX_MODULES];
    int     phys_channel_bPlastTwinPeaks[bPLASTIC_TAMEX_MODULES][100];
    int     leading_hits_ch_bPlastTwinPeaks[bPLASTIC_TAMEX_MODULES][100];
    int     trailing_hits_ch_bPlastTwinPeaks[bPLASTIC_TAMEX_MODULES][100];
    UInt_t    ch_ID_bPlastTwinPeaks[bPLASTIC_TAMEX_MODULES][100];
    double  coarse_T_edge_lead_bPlastTwinPeaks[bPLASTIC_TAMEX_MODULES][100];
    double  coarse_T_edge_trail_bPlastTwinPeaks[bPLASTIC_TAMEX_MODULES][100];
    double  fine_T_edge_lead_bPlastTwinPeaks[bPLASTIC_TAMEX_MODULES][100];
    double  fine_T_edge_trail_bPlastTwinPeaks[bPLASTIC_TAMEX_MODULES][100];
    bool    fired_tamex_bPlastTwinPeaks[bPLASTIC_TAMEX_MODULES];

    // BB7 TWINPEAKS TAMEX
    int     amount_hit_BB7_TWINPEAKS;
    int     iterator_BB7_TWINPEAKS[BB7_TAMEX_MODULES];
    double  trigger_coarse_BB7_TWINPEAKS[100];
    double  trigger_fine_BB7_TWINPEAKS[100];
    int     leading_array_BB7_TWINPEAKS[BB7_TAMEX_MODULES][100];
    int     leading_hits_BB7_TWINPEAKS[BB7_TAMEX_MODULES];
    int     trailing_hits_BB7_TWINPEAKS[BB7_TAMEX_MODULES];
    int     phys_channel_BB7_TWINPEAKS[BB7_TAMEX_MODULES][100];
    int     leading_hits_ch_BB7_TWINPEAKS[BB7_TAMEX_MODULES][100];
    int     trailing_hits_ch_BB7_TWINPEAKS[BB7_TAMEX_MODULES][100];
    UInt_t    ch_ID_BB7_TWINPEAKS[BB7_TAMEX_MODULES][100];
    double  coarse_T_edge_lead_BB7_TWINPEAKS[BB7_TAMEX_MODULES][100];
    double  coarse_T_edge_trail_BB7_TWINPEAKS[BB7_TAMEX_MODULES][100];
    double  fine_T_edge_lead_BB7_TWINPEAKS[BB7_TAMEX_MODULES][100];
    double  fine_T_edge_trail_BB7_TWINPEAKS[BB7_TAMEX_MODULES][100];
    bool    fired_tamex_BB7_TWINPEAKS[BB7_TAMEX_MODULES];

    // BB7 FEBEX
    int         BB7_FEBEX_Hits;
    int         BB7_FEBEX_Side[BB7_FEBEX_MAX_HITS];
    int         BB7_FEBEX_Strip[BB7_FEBEX_MAX_HITS];
    ULong64_t   BB7_FEBEX_Sum_Time[BB7_FEBEX_MAX_HITS];
    ULong64_t   BB7_FEBEX_Chan_Time[BB7_FEBEX_MAX_HITS];
    double      BB7_FEBEX_Chan_Energy[BB7_FEBEX_MAX_HITS];
    ULong64_t   BB7_FEBEX_Chan_CF[BB7_FEBEX_MAX_HITS];
    bool        BB7_FEBEX_Pileup[BB7_FEBEX_MAX_HITS];
    bool        BB7_FEBEX_Overflow[BB7_FEBEX_MAX_HITS];

    // BB7 MADC
    int BB7_MADC_Hits;
    int BB7_MADC_Side[BB7_MADC_MAX_HITS];
    int BB7_MADC_Strip[BB7_MADC_MAX_HITS];
    int BB7_MADC_ADC_Data[BB7_MADC_MAX_HITS];

	//Germanium
        int         Ge_hits;
        int         Germanium_Det_Nums[Germanium_MAX_HITS];
        int         Germanium_Crystal_Nums[Germanium_MAX_HITS];
        ULong64_t   Germanium_sum_time[Germanium_MAX_HITS];
        int         Germanium_hit_pattern[Germanium_MAX_HITS];
        ULong64_t   Germanium_chan_time[Germanium_MAX_HITS];
        double      Germanium_chan_energy[Germanium_MAX_HITS];
        bool        Germanium_Pileup[Germanium_MAX_HITS];
        bool        Germanium_Overflow[Germanium_MAX_HITS];
        ULong64_t   Germanium_chan_cf[Germanium_MAX_HITS];
        //int Event_Type;
        
        int Ge_Tr_Length;
        int Ge_Tr_First[Germanium_MAX_HITS][Germanium_TRACE_LENGTH/2];
        int Ge_Tr_Second[Germanium_MAX_HITS][Germanium_TRACE_LENGTH/2];
        
        ///Beam Monitor
        Long64_t    L_diff_S2[BM_MAX_HITS];
        UInt_t      Hits_S2;
        Long64_t    L_diff_S4[BM_MAX_HITS];
        UInt_t      Hits_S4;

public:
	//Raw_Event(bool);
    Raw_Event();
	~Raw_Event();

	// ##########################################################

	// FRS STUFF //
	void set_DATA_MUSIC(Float_t*,Float_t*,Int_t*,Int_t*,Int_t*,Int_t*);
	void set_DATA_SCI(Float_t*,Float_t*,Float_t*,Float_t*,Float_t*);
	void set_DATA_SCI_dT(Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t);
	void set_DATA_SCI_ToF(Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t);
    void set_DATA_TPC(Int_t***,Int_t***,Float_t*,Float_t*, Int_t**, Int_t**, Int_t**, Int_t***);
    void set_DATA_TPC_S2(Float_t, Float_t, Float_t, Float_t,Float_t,Float_t,Float_t ,Float_t);
    void set_DATA_TPC_S4(Float_t, Float_t, Float_t, Float_t,Float_t,Float_t, Float_t,Float_t);
	void set_DATA_ID_2_4(Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t);
	void set_DATA_ID_Beta_Rho(Float_t*,Float_t*,Float_t,Float_t,Float_t);
	void set_DATA_ID_Z_AoQ(Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t);
	void set_DATA_ID_Timestamp(Float_t,Float_t,Float_t);
    void set_DATA_FRS_SCALERS(Int_t,Int_t,Int_t,Int_t,Int_t,Int_t,Int_t,Int_t,UInt_t*);
  // KW rem
  // void set_DATA_VFTX(Double_t*,Double_t*,Double_t*,Double_t*,Double_t*,Double_t*,Double_t*,Double_t*,Float_t*, Float_t*,Float_t*,Float_t*);
  // KW add S42
  void set_DATA_VFTX(Double_t*,Double_t*,Double_t*,Double_t*,Double_t*,Double_t*,Double_t*,Double_t*,Float_t*, Float_t*,Float_t*,Float_t*,Float_t*, Float_t*,Float_t*,Float_t*);
  
  void set_DATA_ID_VFTX(Float_t*,Float_t*,Float_t*,Float_t*,Float_t*,
			Float_t*,Float_t*,Float_t*,Float_t*,Float_t*,
			Float_t*,Float_t*,Float_t*,Float_t*,Float_t*,
			Float_t*,Float_t*,Float_t*,Float_t*,Float_t*);
  // end KW

    void set_DATA_RAW_MHTDC(Float_t*,Float_t*,Float_t*,Float_t*,Float_t,Float_t,Float_t,Float_t);

    void set_DATA_ID_MHTDC(Float_t*,Float_t*,Float_t*,Float_t*,Float_t*,Float_t*,Float_t*,Float_t*,Float_t,Float_t*);
	
    void set_DATA_Beam_Monitor(Long64_t*, UInt_t,Long64_t*, UInt_t);
    
    // FRS STUFF //


	// ##########################################################
//      void set_DATA_AIDA_DECAY(double***, int, int*, ULong64_t**, int);
//      void set_DATA_AIDA_IMP(double**, int, int*, ULong64_t**, int);

     void set_DATA_AIDA(double*, int*, int*, ULong64_t*, int, bool*, int*, int*, int*, ULong64_t*, int*, std::vector<AidaScaler> const&, std::vector<AidaPauseResume> const&);
     //void Nset_DATA_AIDA(AidaEvent*);

     void set_AIDA_Event(int);

     void set_DATA_FATIMA(int,int,
                         double*,double*,double*,
                         ULong64_t*,double*,
                         ULong64_t*,double*,
                         int*,int*);
    void set_DATA_FATIMA_TAMEX(int*,double**,double**,UInt**,double*,double*,int,int**,uint**,uint**);

    void set_DATA_FINGER(int*,double**,double**,UInt**,double*,double*,int,int**);

    void set_DATA_PLASTIC_TAMEX(int*,double**,double**,UInt**,double*,double*,int,int**,int*);
    
    void set_DATA_PLASTIC_TWINPEAKS(int*,double**,double**,UInt**,double*,double*,int,int**);

    void set_DATA_PLASTIC_VME(int, int, double*, double*, int*, double*, int*);

    void set_DATA_SCALER(int, double*);

    void set_DATA_Germanium(int,ULong64_t*,int*,ULong64_t*,double*,int*,int*,bool*,bool*,ULong64_t*);
    
    void set_DATA_Germanium_Traces(int, int, int**, int**);


    void set_DATA_BB7_FEBEX(int, int*, int*, ULong64_t*, ULong64_t*, double*, ULong64_t*, bool*, bool*);
    void set_DATA_BB7_MADC(int, int*, int*, int*);
    void set_DATA_BB7_TWINPEAKS(int*, double**, double**, UInt**, double*, double*, int, int**);


	// ####################################################


	//temporary FRS getters
	Float_t get_FRS_MusicdE(int);
	Float_t get_FRS_MusicdE_corr(int);
    Int_t get_FRS_MusicE1(int);
    Int_t get_FRS_MusicE2(int);
    Int_t get_FRS_MusicT1(int);
    Int_t get_FRS_MusicT2(int);

	Float_t get_FRS_sci_l(int);
	Float_t get_FRS_sci_r(int);
	Float_t get_FRS_sci_e(int);
	Float_t get_FRS_sci_tx(int);
	Float_t get_FRS_sci_x(int);

	Int_t get_FRS_dt_21l_21r();
	Int_t get_FRS_dt_41l_41r();
	Int_t get_FRS_dt_21l_41l();
	Int_t get_FRS_dt_21r_41r();
	Int_t get_FRS_dt_42l_42r();
	Int_t get_FRS_dt_43l_43r();
	Int_t get_FRS_dt_21l_42l();
	Int_t get_FRS_dt_21r_42r();
	Int_t get_FRS_dt_81l_81r();
	Int_t get_FRS_dt_21l_81l();
	Int_t get_FRS_dt_21r_81r();

	Float_t get_FRS_tofll2();
	Float_t get_FRS_tofll3();
	Float_t get_FRS_tofll5();
	Float_t get_FRS_tofrr2();
	Float_t get_FRS_tofrr3();
    Float_t get_FRS_tofrr5();
    Float_t get_FRS_tof2();
	Float_t get_FRS_tof3();
    Float_t get_FRS_tof5();
    Float_t get_FRS_tof2_calib();
	Float_t get_FRS_tof3_calib();
    Float_t get_FRS_tof5_calib();

	Float_t get_FRS_x2();
	Float_t get_FRS_y2();
	Float_t get_FRS_a2();
	Float_t get_FRS_b2();

	Float_t get_FRS_x4();
	Float_t get_FRS_y4();
	Float_t get_FRS_a4();
	Float_t get_FRS_b4();

    Float_t get_FRS_tpcX(int);
    Float_t get_FRS_tpcY(int);
    Int_t   get_FRS_tpclt(int,int,int);
    Int_t   get_FRS_tpcrt(int,int,int);
    Int_t   get_FRS_tpc_dt(int,int,int);
    Int_t   get_FRS_tpc_a(int, int);
    Int_t   get_FRS_tpc_r(int, int);
    Int_t   get_FRS_tpc_l(int, int);
    
//     Float_t get_FRS_tpcx0();
//     Float_t get_FRS_tpcx1();
    Float_t get_FRS_tpc_x_s2_foc_23_24();
    Float_t get_FRS_tpc_y_s2_foc_23_24();
    Float_t get_FRS_tpc_x_angle_s2_foc_23_24();
    Float_t get_FRS_tpc_y_angle_s2_foc_23_24();
    Float_t get_FRS_tpc23_24_x_sc21();
    Float_t get_FRS_tpc23_24_y_sc21();
    Float_t get_FRS_tpc23_24_x_sc22();
    Float_t get_FRS_tpc23_24_y_sc22();
    
    Float_t get_FRS_tpc_x_s4();
    Float_t get_FRS_tpc_y_s4();
    Float_t get_FRS_tpc_x_angle_s4();
    Float_t get_FRS_tpc_y_angle_s4();
    Float_t get_FRS_tpc_x_sc41();
    Float_t get_FRS_tpc_y_sc41();
    Float_t get_FRS_tpc_x_sc42();
    Float_t get_FRS_tpc_y_sc42();
	Float_t get_FRS_brho(int);
	Float_t get_FRS_rho(int);

	Float_t get_FRS_beta();
	Float_t get_FRS_beta3();
	Float_t get_FRS_gamma();

	Float_t get_FRS_AoQ();
	Float_t get_FRS_AoQ_corr();
	Float_t get_FRS_z();
	Float_t get_FRS_z2();
	Float_t get_FRS_z3();
    Float_t get_FRS_dEdeg();
    Float_t get_FRS_dEdegoQ();

	Float_t get_FRS_timestamp();
	Float_t get_FRS_ts();
	Float_t get_FRS_ts2();

    Int_t   get_FRS_time_in_ms();
    Int_t   get_FRS_spill_count();
    Int_t   get_FRS_ibin_for_s();
    Int_t   get_FRS_ibin_for_100ms();
    Int_t   get_FRS_ibin_for_spill();
    Int_t   get_FRS_ibin_clean_for_s();
    Int_t   get_FRS_ibin_clean_for_100ms();
    Int_t   get_FRS_ibin_clean_for_spill();
    UInt_t*  get_FRS_increase_scaler_temp();
    
  

   Double_t get_FRS_TRaw_vftx_21l(int i);
    Double_t get_FRS_TRaw_vftx_21r(int i);
    Double_t get_FRS_TRaw_vftx_22l(int i);
    Double_t get_FRS_TRaw_vftx_22r(int i);
    Double_t get_FRS_TRaw_vftx_41l(int i);
    Double_t get_FRS_TRaw_vftx_41r(int i);
    Double_t get_FRS_TRaw_vftx_42l(int i);
    Double_t get_FRS_TRaw_vftx_42r(int i);
    Float_t get_FRS_ToF_vftx_2141(int i);
    Float_t get_FRS_ToF_vftx_2141_calib(int i);
    Float_t get_FRS_ToF_vftx_2241(int i);
    Float_t get_FRS_ToF_vftx_2241_calib(int i);
  //KW add
  Float_t get_FRS_ToF_vftx_2142(int i);
  Float_t get_FRS_ToF_vftx_2142_calib(int i);
  Float_t get_FRS_ToF_vftx_2242(int i);
  Float_t get_FRS_ToF_vftx_2242_calib(int i);
  
  Float_t get_FRS_vftx_aoq_2141(int i){ return ID_vftx_aoq_2141[i];}
  Float_t get_FRS_vftx_aoq_corr_2141(int i){ return ID_vftx_aoq_corr_2141[i];}
  Float_t get_FRS_vftx_z_2141(int i){ return ID_vftx_z_2141[i];}
  Float_t get_FRS_vftx_z2_2141(int i){ return ID_vftx_z2_2141[i];}
  Float_t get_FRS_vftx_beta_2141(int i){ return ID_vftx_beta_2141[i];}
                        
  Float_t get_FRS_vftx_aoq_2241(int i){ return ID_vftx_aoq_2241[i];}
  Float_t get_FRS_vftx_aoq_corr_2241(int i){ return ID_vftx_aoq_corr_2241[i];}
  Float_t get_FRS_vftx_z_2241(int i){ return ID_vftx_z_2241[i];}
  Float_t get_FRS_vftx_z2_2241(int i){ return ID_vftx_z2_2241[i];}
  Float_t get_FRS_vftx_beta_2241(int i){ return ID_vftx_beta_2241[i];}
  
  Float_t get_FRS_vftx_aoq_2142(int i){ return ID_vftx_aoq_2142[i];}
  Float_t get_FRS_vftx_aoq_corr_2142(int i){ return ID_vftx_aoq_corr_2142[i];}
  Float_t get_FRS_vftx_z_2142(int i){ return ID_vftx_z_2142[i];}
  Float_t get_FRS_vftx_z2_2142(int i){ return ID_vftx_z2_2142[i];}
  Float_t get_FRS_vftx_beta_2142(int i){ return ID_vftx_beta_2142[i];}
  
  Float_t get_FRS_vftx_aoq_2242(int i){ return ID_vftx_aoq_2242[i];}
  Float_t get_FRS_vftx_aoq_corr_2242(int i){ return ID_vftx_aoq_corr_2242[i];}
  Float_t get_FRS_vftx_z_2242(int i){ return ID_vftx_z_2242[i];}
  Float_t get_FRS_vftx_z2_2242(int i){ return ID_vftx_z2_2242[i];}
  Float_t get_FRS_vftx_beta_2242(int i){ return ID_vftx_beta_2242[i];}

  // end KW

  
    Float_t get_FRS_Raw_mhtdc_sc21lr_dt(int i );
    Float_t get_FRS_Raw_mhtdc_sc21lr_x(int i);
    Float_t get_FRS_Raw_mhtdc_sc22lr_dt(int i);
    Float_t get_FRS_Raw_mhtdc_sc22lr_x(int i);
    Float_t get_FRS_Raw_mhtdc_sc41lr_dt();
    Float_t get_FRS_Raw_mhtdc_sc41lr_x();
    Float_t get_FRS_Raw_mhtdc_sc42lr_dt();
    Float_t get_FRS_Raw_mhtdc_sc42lr_x();

    Float_t get_FRS_id_mhtdc_aoq(int);
    Float_t get_FRS_id_mhtdc_aoq_corr(int);
    Float_t get_FRS_id_mhtdc_z1(int);
    Float_t get_FRS_id_mhtdc_z2(int);
    Float_t get_FRS_id_mhtdc_dEdeg(int);
    Float_t get_FRS_id_mhtdc_dEdegoQ(int);
    Float_t get_FRS_id_mhtdc_beta(int);
    Float_t get_FRS_id_mhtdc_tof4121(int);
    Float_t get_FRS_id_mhtdc_tof4221();
    Float_t get_FRS_id_mhtdc_tof4122(int);


	// ####################################################
    double  get_AIDA_Energy(int i);
    int     get_AIDA_FEE_ID(int i);
    int     get_AIDA_CHA_ID(int i);
    ULong64_t get_AIDA_WR(int i);
    int     get_AIDA_HITS();
    bool    get_AIDA_HighE_VETO(int i);
    int     get_AIDA_SIDE(int i);
    int     get_AIDA_STRIP(int i);
    int     get_AIDA_EVTID(int i);
	ULong64_t get_AIDA_FastTime(int i);
	int     get_AIDA_ADC(int i);
	std::vector<AidaScaler> const& get_AIDA_scaler() { return AIDA_SCALERS; }
	std::vector<AidaPauseResume> const& get_AIDA_pr() { return AIDA_PAUSERESUME; }

	//temporary FATIMA getters
	  int    get_FAT_det_fired();
	  int    get_FAT_id(int i);
      double get_FAT_E(int i);
      double get_FAT_ratio(int i);
      double get_FAT_t(int i);
      double get_FAT_t_qdc(int i);

      int    get_FAT_QDCs_fired();
      int    get_FAT_QDC_id(int i);
      double get_FAT_QLong(int i);
      double get_FAT_QShort_Raw(int i);
      double get_FAT_QLong_Raw(int i);
      ULong64_t get_FAT_QDC_t_Coarse(int i);
      double get_FAT_QDC_t_Fine(int i);

      int    get_FAT_TDCs_fired();
	  int    get_FAT_TDC_id(int i);
      double get_FAT_TDC_timestamp(int i);
      double get_FAT_TDC_timestamp_raw(int i);
      //temporary FATIMA TAMEX getters
    int     get_FATIMA_am_Fired(int);
    double  get_FATIMA_trigger_T(int);
    int     get_FATIMA_CH_ID(int,int);
    double  get_FATIMA_lead_T(int,int);
    double  get_FATIMA_trail_T(int,int);
    int     get_FATIMA_trail_hits(int);
    int     get_FATIMA_lead_hits(int);
    int     get_FATIMA_physical_channel(int,int);
    int     get_FATIMA_physical_lead_hits(int,int);
    int     get_FATIMA_physical_trail_hits(int,int);
    double  get_FATIMA_coarse_lead(int,int);
    double  get_FATIMA_fine_lead(int,int);
    double  get_FATIMA_coarse_trail(int,int);
    double  get_FATIMA_fine_trail(int,int);
    double  get_FATIMA_TOT(int,int);
    double  get_FATIMA_TOT_added(int,int);
    int     get_FATIMA_tamex_hits();
    double  get_FATIMA_Lead_Lead(int,int);

    //temporary bPlast TAMEX getters
    int     get_bPLAST_TWINPEAKS_am_Fired(int);
    double  get_bPLAST_TWINPEAKS_trigger_T(int);
    int     get_bPLAST_TWINPEAKS_CH_ID(int,int);
    double  get_bPLAST_TWINPEAKS_lead_T(int,int);
    double  get_bPLAST_TWINPEAKS_trail_T(int,int);
    int     get_bPLAST_TWINPEAKS_trail_hits(int);
    int     get_bPLAST_TWINPEAKS_lead_hits(int);
    int     get_bPLAST_TWINPEAKS_physical_channel(int,int);
    int     get_bPLAST_TWINPEAKS_physical_lead_hits(int,int);
    int     get_bPLAST_TWINPEAKS_physical_trail_hits(int,int);
    double  get_bPLAST_TWINPEAKS_coarse_lead(int,int);
    double  get_bPLAST_TWINPEAKS_fine_lead(int,int);
    double  get_bPLAST_TWINPEAKS_coarse_trail(int,int);
    double  get_bPLAST_TWINPEAKS_fine_trail(int,int);
    double  get_bPLAST_TWINPEAKS_TOT(int,int);
    double  get_bPLAST_TWINPEAKS_TOT_added(int,int);
    int     get_bPLAST_TWINPEAKS_tamex_hits();
    double  get_bPLAST_TWINPEAKS_Lead_Lead(int,int);

    // ----------------   BB7 TWINPEAKS Getters ---------------- //
    int     get_BB7_TWINPEAKS_am_Fired(int);
    double  get_BB7_TWINPEAKS_trigger_T(int);
    int     get_BB7_TWINPEAKS_CH_ID(int,int);
    double  get_BB7_TWINPEAKS_lead_T(int,int);
    double  get_BB7_TWINPEAKS_trail_T(int,int);
    int     get_BB7_TWINPEAKS_trail_hits(int);
    int     get_BB7_TWINPEAKS_lead_hits(int);
    int     get_BB7_TWINPEAKS_physical_channel(int,int);
    int     get_BB7_TWINPEAKS_physical_lead_hits(int,int);
    int     get_BB7_TWINPEAKS_physical_trail_hits(int,int);
    double  get_BB7_TWINPEAKS_coarse_lead(int,int);
    double  get_BB7_TWINPEAKS_fine_lead(int,int);
    double  get_BB7_TWINPEAKS_coarse_trail(int,int);
    double  get_BB7_TWINPEAKS_fine_trail(int,int);
    double  get_BB7_TWINPEAKS_TOT(int,int);
    double  get_BB7_TWINPEAKS_TOT_added(int,int);
    int     get_BB7_TWINPEAKS_tamex_hits();
    double  get_BB7_TWINPEAKS_Lead_Lead(int,int);
    int     get_BB7_TWINPEAKS_leading_arr(int,int);

    // BB7 FEBEX Getters
    int         get_BB7_FEBEX_Hits();
    int         get_BB7_FEBEX_Side(int);
    int         get_BB7_FEBEX_Strip(int);
    ULong64_t   get_BB7_FEBEX_Sum_Time(int);
    ULong64_t   get_BB7_FEBEX_Chan_Time(int);
    double      get_BB7_FEBEX_Chan_Energy(int);
    ULong64_t   get_BB7_FEBEX_Chan_CF(int);
    bool        get_BB7_FEBEX_Pileup(int);
    bool        get_BB7_FEBEX_Overflow(int);

    // BB7 MADC Getters
    int get_BB7_MADC_Hits();
    int get_BB7_MADC_ADC(int);
    int get_BB7_MADC_Side(int);
    int get_BB7_MADC_Strip(int);

    // ------------------------------------------------------------///


    //temporary FINGER getters
    int     get_FINGER_am_Fired(int);
    double  get_FINGER_trigger_T(int);
    int     get_FINGER_CH_ID(int,int);
    double  get_FINGER_lead_T(int,int);
    double  get_FINGER_trail_T(int,int);
    int     get_FINGER_trail_hits(int);
    int     get_FINGER_lead_hits(int);
    int     get_FINGER_physical_channel(int,int);
    int     get_FINGER_physical_lead_hits(int,int);
    int     get_FINGER_physical_trail_hits(int,int);
    double  get_FINGER_coarse_lead(int,int);
    double  get_FINGER_fine_lead(int,int);
    double  get_FINGER_coarse_trail(int,int);
    double  get_FINGER_fine_trail(int,int);
    double  get_FINGER_TOT(int,int);
    double  get_FINGER_TOT_added(int,int);
    int     get_FINGER_tamex_hits();

	//temporary PLASTIC getters
	int     get_PLASTIC_am_Fired(int);
    int     get_PLASTIC_TAMEX_ID(int);
    double  get_PLASTIC_trigger_T(int);
    int     get_PLASTIC_CH_ID(int,int);
    double  get_PLASTIC_lead_T(int,int);
    double  get_PLASTIC_trail_T(int,int);
    int     get_PLASTIC_trail_hits(int);
    int     get_PLASTIC_lead_hits(int);
    int     get_PLASTIC_physical_channel(int,int);
    int     get_PLASTIC_physical_lead_hits(int,int);
    int     get_PLASTIC_physical_trail_hits(int,int);
    double  get_PLASTIC_coarse_lead(int,int);
    double  get_PLASTIC_fine_lead(int,int);
    double  get_PLASTIC_coarse_trail(int,int);
    double  get_PLASTIC_fine_trail(int,int);
    double  get_PLASTIC_TOT(int,int);
   // double  get_PLASTIC_TOT_added(int,int);
    int     get_PLASTIC_tamex_hits();

// 	PLASTIC_VME_DataStruct* PassPLASTIC_VME();
// 	PLASTIC_DataStruct* PassPLASTIC();
//     int     get_plastic_VME_QDC_fired();
//     int     get_plastic_VME_TDC_fired();
//     double  get_plastic_VME_QDC_dat1(int);
//     double  get_plastic_VME_QDC_dat2(int);
//     int     get_plastic_VME_QDC_cha(int);
//     double  get_plastic_VME_TDC_dat(int);
//     int     get_plastic_VME_TDC_cha(int);

    int     get_scaler_iterator();
    double  get_scaler_data(int);


	//temporary Germanium getters
        int         get_Germanium_am_Fired();
        ULong64_t   get_Germanium_Event_T(int);

        int         get_Germanium_Hit_Pattern(int);
        ULong64_t   get_Germanium_Chan_T(int);
        double      get_Germanium_Chan_E(int);
        int         get_Germanium_Det_id(int);
        int         get_Germanium_Crystal_id(int);
        bool        get_Germanium_Pileup(int);
        bool        get_Germanium_Overflow(int);
        ULong64_t   get_Germanium_Channel_cf(int);
        int         get_Germanium_Trace_Length();
        int         get_Germanium_Trace_First(int,int);
        int         get_Germanium_Trace_Second(int,int);
        
        ///Beam Monitor
        Long64_t  get_BM_LDiff_S2(int i);
        UInt_t    get_BM_Hits_S2();
        Long64_t  get_BM_LDiff_S4(int i);
        UInt_t    get_BM_Hits_S4();
        

	//White Rabbit setter and getter
	void set_WR(ULong64_t);
	ULong64_t get_WR();


};


#endif
