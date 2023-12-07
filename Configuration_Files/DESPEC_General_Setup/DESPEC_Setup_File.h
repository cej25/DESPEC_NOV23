///Should be set for each experiment depending upon configuration
#ifndef DESPEC_SETUP_FILE
#define DESPEC_SETUP_FILE

///Note that channels start from 0

#define WHITE_RABBIT_ENABLED 1
#define NUM_SUBSYS 11 // CEJ: number of subsystems for wr/procid

///Use FRS MHTDC for Analysis (1) or NIM TAC (0)
#define MHTDC_OR_TAC 0
///Use FRS angle corrected A/Q for Analysis (1) or none-corrected (0)
#define FRS_CORR 1
///For Z1 Z2 AND X A/Q Gate: Use FRS X2 vs A/Q (1) OR X4 vs A/Q (0) 
#define X2_or_X4 0
//Set the white rabbit offset time in minutes for the FRS (used only for gain matching of Z and A/Q over time): Defined in the EventUnpackProc and used in FRS_Detector_System
#define FRS_WR_GAINOFFSET 26900000
//Define Number of FRS Histogram bins for 2D plots
#define FRS_HISTO_BIN 750

//#define FRS_MIN_AoQ 2.0
//#define FRS_MAX_AoQ 3.0
//#define FRS_MIN_Z 30
//#define FRS_MAX_Z 90
///Use High charge state gate for Correlations
//#define USE_dEdeg_Z1_GATE 0

///Define number of FRS gates and Polygon Points
#define MAX_FRS_GATE 8
///Fix this
#define MAX_FRS_PolyPoints 50

#define FINGER_TAMEX_MODULES 4
#define FINGER_TAMEX_HITS    512

///FATIMA VME 
#define FAT_TDC_NUMBER 2
#define SCALER_MODULE_ON 1
#define FAT_MAX_VME_CHANNELS 51 
#define FAT_TDC_REF_CHANNEL 1
#define FAT_VME_MAX_MULTI 51
#define SC41L_FatVME  36
#define SC41R_FatVME  37
#define SC41L_FatVME_Digi  38
#define SC41R_FatVME_Digi  39
#define FatVME_TimeMachineCh1 13
#define FatVME_TimeMachineCh2 14
#define FatVME_bPlast_UP 42
#define FatVME_bPlast_DOWN 43
#define FatVME_bPlast_MASTER 44
#define FatVME_bPlast_StartCh 45
#define FatVME_bPlast_StopCh 50
#define FatGM_Offset 26916384
///FATIMA TAMEX
#define FATIMA_TAMEX_MODULES 4
#define FATIMA_TAMEX_HITS 50
#define FATIMA_TAMEX_CHANNELS 65
#define FATIMA_TAMEX_SC41L  3
#define FATIMA_TAMEX_SC41R  4 
#define FATIMA_TAMEX_SC41L_Digi  51
#define FATIMA_TAMEX_SC41R_Digi  52
#define FatTAMEX_TimeMachineCh1 1
#define FatTAMEX_TimeMachineCh2 2

// BB7 LAYER
#define BB7_DETECTORS 1
#define BB7_SIDES 5 // 2 for Nov tests
#define BB7_STRIPS_PER_SIDE 32 // up to
#define BB7_IMPLANT_E_THRESHOLD 600000 // keV // made up for compilation, change// 
#define BB7_FRONT_BACK_E_GATE_IMPLANT 200 // keV
#define BB7_FRONT_BACK_E_GATE_DECAY 200
#define BB7_FRONT_BACK_T_GATE 200 // no idea
#define BB7_XLENGTH 65.18 // inner L, 68.08 outer L, unsure.
#define BB7_YLENGTH 65.18

#define BB7_FEBEX_MODULES 4
#define BB7_FEBEX_CHAN_PER_MOD 16
#define BB7_FEBEX_MAX_CHANNELS (BB7_FEBEX_MODULES * BB7_FEBEX_CHAN_PER_MOD)
#define BB7_FEBEX_MAX_HITS BB7_FEBEX_MAX_CHANNELS
#define BB7_FEBEX_TM_SIDE1 0
#define BB7_FEBEX_TM_SIDE2 0
#define BB7_FEBEX_TM_STRIP1 0
#define BB7_FEBEX_TM_STRIP2 1
#define BB7_TAMEX_MODULES 9 // CEJ: USE 9 FOR TRICKING PLASTIC DATA
#define BB7_TAMEX_CHANNELS 16 // CEJ: 32 tdc channels, 16 * fast+slow tamex channels
#define BB7_TAMEX_MAX_HITS 200
#define BB7_TAMEX_ANL_HITS 5 // why is this 5 and max hits for unpacking is 200?
#define BB7_TWINPEAKS_TM_SIDE1 4
#define BB7_TWINPEAKS_TM_SIDE2 4
#define BB7_TWINPEAKS_TM_STRIP1 9
#define BB7_TWINPEAKS_TM_STRIP2 8
#define BB7_MADC_MODULES 2
#define BB7_MADC_CHANNELS 32
#define BB7_MADC_MAX_HITS (BB7_MADC_MODULES * BB7_MADC_CHANNELS)

///bPLASTIC 
///1:twin peaks,  0 for pQDC 
#define bPLASTIC_TWINPEAKS 1
#define bPLASTIC_DETECTORS 1 // 
///TAMEX: 3 for narrow, 9 for wide
#define bPLASTIC_TAMEX_MODULES 9
#define bPLASTIC_TAMEX_HITS 5
#define bPLASTIC_TAMEX_CHANNELS 16
///bPlastic number of channels per detector (16 for narrow, 64 for wide)
#define bPLASTIC_CHAN_PER_DET 64
///bPlastic Upstream Detector
#define bPLASTIC_UPSTREAM_DET 1
///bPlastic Downstream Detector
#define bPLASTIC_DOWNSTREAM_DET 2
///bPlast Additional signals Module Num
#define bPLASTIC_ADDITIONAL_CH_MOD 1
///bPlast Additional signals Channel Num
#define bPLASTIC_FATTAMEX 9
#define bPLASTIC_FATVME 8
#define SC41L_bPLASTIC 36
#define SC41R_bPLASTIC 37
#define bPLASTIC_OR_UP_DOWN 13
#define bPLASTIC_UP_COIN 1
#define bPLASTIC_DOWN_COIN 3
#define bPLASTIC_Ge_TRIGGER 11 //accepted trigger for S450
//Add ge trigger

///bPlast Time Machine Channels
#define bPlastTimeMachineCh1 34
#define bPlastTimeMachineCh2 35
///bPlastic reference channels
#define bPlastRefCh_Det1 0
#define bPlastRefCh_Det2 0
#define bPlastRefCh_Det3 0

///FIBRE
#define FIBRE_BOARD 3

///Germanium (including additional channel detectors (e.g.SC41 det)
#define Germanium_TRACES_ACTIVE 0
#define Germanium_TRACE_LENGTH 2000
#define Germanium_MAX_DETS 16
#define Germanium_CRYSTALS 7
#define Germanium_MAX_HITS (Germanium_MAX_DETS * Germanium_CRYSTALS)
///Important for FEBEX
#define Germanium_FEBEX_MODULES 4
#define Germanium_MAX_CHANNELS 69
///Define here where SC41 is plugged into FEBEX ("Detector" and "crystal" for mapping purposes) Use the germanium allocation file for mapping of this
#define Germanium_SC41_Det 11
#define Germanium_SC41L_Crystal 0
#define Germanium_SC41R_Crystal 1
#define Germanium_SC41_Det_Digi 11
#define Germanium_SC41L_Crystal_Digi 0
#define Germanium_SC41R_Crystal_Digi 15
#define Germanium_TimeMachine_Det 11
#define Germanium_TimeMachineCh1 1
#define Germanium_TimeMachineCh2 2

#define AIDA_MAX_HITS 13000
///Max hits for the beam monitor
#define BM_MAX_HITS 100000

#endif /* DESPEC_SETUP_FILE */
