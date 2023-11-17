#include "BB7_MADC_Detector_System.h"

#include <cstdlib>
#include <map>

#include "MADC32.h"
#include "Configuration_Files/DESPEC_General_Setup/DESPEC_Setup_File.h"

BB7_MADC_Detector_System::BB7_MADC_Detector_System()
{
    max_hits = BB7_MADC_MAX_HITS;
    num_modules = BB7_MADC_MODULES;

    Side = new int[max_hits];
    Strip = new int[max_hits];
    ADC_Data = new int[max_hits];

    Hits = 0;
    for (int i = 0; i < max_hits; i++)
    {   
        Side[i] = 0;
        Strip[i] = 0;
        ADC_Data[i] = 0;
    }

    load_board_channel_file();

    // do we care about channel time?
}

BB7_MADC_Detector_System::~BB7_MADC_Detector_System()
{
    BB7_MADC_Map.clear();
    delete[] Side;
    delete[] Strip;
    delete[] ADC_Data;
}

void BB7_MADC_Detector_System::load_board_channel_file()
{   
    std::ifstream file("Configuration_Files/BB7/BB7_MADC_Detector_Map.txt");
    std::cout << "Loading BB7 MADC Detector Map" << std::endl;
    if (file.fail())
    {
        std::cerr << "Could not find BB7 MADC Mapping!" << std::endl;
        exit(0);
    }

    constexpr auto ignore = std::numeric_limits<std::streamsize>::max();

    while (file.good())
    {
        if (file.peek() == '#')
        {
            file.ignore(ignore, '\n');
            continue;
        }

        // #module_id, channel_id, side, strip_number
        int mod, chan, side, strip;
        file >> mod >> chan >> side >> strip;
        file.ignore(ignore, '\n');

        BB7_MADC_Map[std::make_pair(mod, chan)] = std::make_pair(side, strip);
    }
}

void BB7_MADC_Detector_System::get_Event_data(Raw_Event* RAW)
{
    RAW->set_DATA_BB7_MADC(Hits, Side, Strip, ADC_Data);
}

void BB7_MADC_Detector_System::Process_MBS(int* pdata)
{   
    this->pdata = pdata;

    for (int i = 0; i < num_modules; i++)
    {

        ADC_Header* header = (ADC_Header*) pdata;
        if (header->sig != 0b01)
        {
            std::cerr << "Can't match header word in MADC32! Word: " << std::hex << *pdata << std::endl;
        }

        adc_words = header->words;
        module_id = header->module_id; // needed for map
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
            channel_id = data->channel;

            auto idx = std::make_pair(module_id, channel_id);
            Side[Hits] = BB7_MADC_Map[idx].first;
            Strip[Hits] = BB7_MADC_Map[idx].second;
            ADC_Data[Hits] = data->measurement;

            Hits++;
            pdata++;

        } // word loop

        ADC_End* eoe = (ADC_End*) pdata;
        if (eoe->sig != 0b11)
        {
            std::cerr << "Can't match end of event word in MADC32! Word: " << std::hex << *pdata << std::dec << std::endl;
        }

    } // module loop
}

int* BB7_MADC_Detector_System::get_pdata() { return pdata; }
