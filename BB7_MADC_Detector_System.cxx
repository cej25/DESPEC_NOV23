#include "BB7_MADC_Detector_System.h"

#include <cstdlib>
#include <map>

#include "MADC32.h"
#include "Configuration_Files/DESPEC_General_Setup/DESPEC_Setup_File.h"

BB7_MADC_Detector_System::BB7_MADC_Detector_System()
{
    max_hits = BB7_MADC_MAX_HITS;
    num_modules = BB7_MADC_MODULES;

    Module_ID = new int[max_hits];
    Side = new int[max_hits];
    Strip = new int[max_hits];
    AdcData = new int[max_hits];
    Hit_Pattern = new int[max_hits];


    for (int i = 0; i < max_hits; i++)
    {
        Module_ID[i] = 0;
        Side[i] = 0;
        Strip[i] = 0;
        AdcData[i] = 0;
        Hit_Pattern[i] = 0;
    }

    // do we care about channel time?
}

BB7_MADC_Detector_System::~BB7_MADC_Detector_System()
{
    // BB7_MADC_Map.clear();
    delete[] Module_ID;
    delete[] Side;
    delete[] Strip;
    delete[] AdcData;
    delete[] Hit_Pattern;
}

void BB7_MADC_Detector_System::load_board_channel_file()
{   
    // CEJ:
    // here we should load strip mapping
    // we can make pair of module_id and channel_id
    // and find which strip this maps to 
    // horizontal or vertical? maybe its implicit 
    // probably can't be assumed.
    // Check AIDA mapping
}

void BB7_MADC_Detector_System::get_Event_Data(Raw_Event* RAW)
{
    RAW->set_DATA_BB7_MADC(int* Module_ID, int* Side, int* Strip, int* AdcData, int* Hit_Pattern);
}

void BB7_MADC_Detector_System::Process_MBS(int* pdata)
{   
    this->pdata = pdata;

    // we should match channel to strip here
    // must match how AIDA deals with this.

    for (int i = 0; i < num_modules; i++)
    {

        ADC_Header* header = (ADC_Header*) pdata;
        if (header->sig != 0b01)
        {
            std::cerr << "Can't match header word in MADC32! Word: " << std::hex << *pdata << std::endl;
        }

        adc_words = header->words;
        module_id = header->module_id;
        pdata++;

        // loop over words
        for (int word = 0; word < adc_words - 1; word++)
        {   
            // check for filler word
            if (word == adc_words - 2)
            {
                ADC_Fill* fill = (ADC_Fill*) pdata;
                if (fill->zero == 0)
                {
                    pdata++;
                    continue;
                }
            }

            // CEJ: should we check adc measurement vs ext_ts?

            ADC_Measurement* data = (ADC_Measurement*) pdata;
            AdcData[data->channel] = data->measurement;
            Hit_Pattern[data->channel] = 1;

            // match side and strip
            // in AIDA...
            // Side = conf->FEE(feeID).Side;
            // Strip = {127 -} FeeToStrip[channelID];

            pdata++;

        } // word loop

        ADC_End* eoe = (ADC_End*) pdata;
        if (eoe->sig != 0b11)
        {
            std::cerr << "Can't match end of event word in MADC32! Word: " << std::hex << *pdata << std::dec << std::endl;
        }

    } // module loop
}

void BB7_MADC_Detector_System::get_pdata() { return pdata; }
