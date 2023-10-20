#ifndef MADC32_H
#define MADC32_H

#include <iostream>
#include <string>
#include <sstream>

struct ADC_Header
{       
    unsigned int words: 12; // includes ADC_End
    unsigned int res: 3;
    unsigned int format: 1;
    unsigned int module_id: 8;
    unsigned int subsig: 6;
    unsigned int sig: 2; // b01 = header
};

struct ADC_Measurement
{   
    unsigned int measurement: 13; // 11..13, sometimes msbits are 00?
    unsigned int oor: 1;
    unsigned int zero: 1;
    unsigned int channel: 5;
    unsigned int type: 9; // b00 0100 000 = data, b00 0100 100 = extended ts
    unsigned int sig: 2; // b00 = data
};

// possibly not required...
struct ADC_Extended_TS
{
    unsigned int ext_ts: 16; // high part of TS - where is low?
    unsigned int zero: 5;
    unsigned int type: 9; // b00 0100 000 = data, b00 0100 100 = extended ts
    unsigned int sig: 2; // b00 = data
};

struct ADC_Fill // when data words are "odd"
{
    unsigned int zero: 32;
};

struct ADC_End
{
    unsigned int count: 30; // event counter / timestamp?
    unsigned int sig: 2; // b11 = eoe
};


#endif