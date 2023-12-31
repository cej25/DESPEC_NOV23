#ifndef WHITE_RABBIT_H
#define WHITE_RABBIT_H

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

#include "WR_Structure.h"
#include "Configuration_Files/DESPEC_General_Setup/DESPEC_Setup_File.h"


//define ULong64_t (used e.g. in Root or Go4)
typedef unsigned long long ULong64_t;

class White_Rabbit{

private:
    // CEJ: this shouldn't defined this twice!!!!
    const std::string names[NUM_SUBSYS] = {"FRS","AIDA","PLASTIC","FATIMA","FATIMA_TAMEX","GERMANIUM","FINGER","BEAM_MONITOR", "BB7_FEBEX", "BB7_TWINPEAKS", "BB7_MADC"};
    int increase;
    int DETECTORS[NUM_SUBSYS]; // what is this used for?
    int ID[NUM_SUBSYS];

    int* pdata;

    int detector_id;
    ULong64_t WR_Time;

    void load_config_file();
    int get_Detector_type();

    void set_triggered_detector(int);
    void process_White_Rabbit(int*);



public:
    White_Rabbit();
    White_Rabbit(bool);
    ~White_Rabbit();

    void set_WR_from_MASTER_DET(ULong64_t);

    ULong64_t get_White_Rabbit(int*);
    int get_Detector_id();

    int* get_pdata();

    
};


#endif
