#include "BB7_FEBEX_Detector_System.h"

#include <cstdlib>
#include <map>

#include "FEBEX.h"
#include "Configuration_Files/DESPEC_General_Setup/DESPEC_Setup_File.h"

// using namespace std;

BB7_FEBEX_Detector_System::BB7_FEBEX_Detector_System()
{
    // set amount of detectors
    max_hits = BB7_FEBEX_MAX_HITS;
    num_modules = BB7_FEBEX_MODULES;

    Side = new int[max_hits];
    Strip = new int[max_hits];
    Sum_Time = new ULong64_t[max_hits];
    Chan_Time = new ULong64_t[max_hits];
    Chan_Energy = new double[max_hits];
    Chan_CF = new ULong64_t[max_hits];
    Pileup = new bool[max_hits];
    Overflow = new bool[max_hits];

    load_board_channel_file();
}

BB7_FEBEX_Detector_System::~BB7_FEBEX_Detector_System()
{
    BB7_FEBEX_Map.clear(); // note from AKM that this is maybe not necessary
    delete[] Side;
    delete[] Strip;
    delete[] Sum_Time;
    delete[] Pileup;
    delete[] Overflow;
    delete[] Chan_Time;
    delete[] Chan_Energy;
    delete[] Chan_CF;
}

void BB7_FEBEX_Detector_System::load_board_channel_file()
{
    std::ifstream file("Configuration_Files/BB7/BB7_FEBEX_Detector_Map.txt");
    std::cout << "Loading BB7 FEBEX Detector Map" << std::endl;
    if (file.fail())
    {
        std::cerr << "Could not find BB7 FEBEX Mapping" << std::endl;
        exit(0);
    }

    constexpr auto ignore = std::numeric_limits<streamsize>::max();

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

        //std::cout << "mod, chan, side, strip" << std::endl;
        //std::cout << mod << " : " << chan << " : " << side << " : " <<  strip << std::endl;

        BB7_FEBEX_Map[std::make_pair(mod, chan)] = std::make_pair(side, strip);
    }
}

void BB7_FEBEX_Detector_System::get_Event_data(Raw_Event* RAW)
{   
    RAW->set_DATA_BB7_FEBEX(Hits, Side, Strip, Sum_Time, Chan_Time, Chan_Energy, Chan_CF, Pileup, Overflow);
}

void BB7_FEBEX_Detector_System::Process_MBS(int* pdata)
{   
    this->pdata = pdata; // CEJ: i hate this
    reset_fired_channels();

    // loop through padding
    FEBEX_Add* FEBEX_add = (FEBEX_Add*) this->pdata;
    while (FEBEX_add->add == 0xADD)
    {
        this->pdata++;
        FEBEX_add = (FEBEX_Add*) this->pdata;
    }

    FEBEX_Header* SumChannel_Head = (FEBEX_Header*) this->pdata;

    bool FEBEX_data_loop = true;
    while (FEBEX_data_loop)
    {
        if (SumChannel_Head->ff == 0xFF)
        {
            module_id = SumChannel_Head->chan_head;
            this->pdata++;

            FEBEX_Chan_Size* Channel_Size = (FEBEX_Chan_Size*) this->pdata;
            num_channels = ((Channel_Size->chan_size) / 4) - 1;
            if (num_channels == 0) num_modules--;
            this->pdata++;

            FEBEX_Half_Time* EventTime_Hi = (FEBEX_Half_Time*) this->pdata;
            tmp_EventTime_hi = EventTime_Hi->ext_time;
            this->pdata++;

            FEBEX_Evt_Time* EventTime_Lo = (FEBEX_Evt_Time*) this->pdata;
            
            tmp_Sum_Time = (EventTime_Lo->evt_time) + (tmp_EventTime_hi << 32);
            this->pdata++;

            FEBEX_Flag_Hits* Flags = (FEBEX_Flag_Hits*) this->pdata;
            tmp_Pileup = Flags->pile_flags;
            tmp_Hit_Pattern = Flags->hit_pattern;

            // none of this seemed correct for modules>1
            // we can rework if we need a hit pattern by module

            this->pdata++;

        } // FF header
        else if (SumChannel_Head->ff == 0xF0)
        {
            this->pdata--; // move back to DEADBEEF for this loop to work

            for (int i = 0; i < num_channels; i++)
            {   
                std::cout << "pdata: " << std::hex << *this->pdata << std::dec << std::endl;
                this->pdata++;

                FEBEX_Chan_Header* Channel_Head = (FEBEX_Chan_Header*) this->pdata;
                channel_id = Channel_Head->Ch_ID;
                tmp_ChanTime_hi = Channel_Head->ext_chan_ts;

                // CEJ: is this necessary here?
                auto idx = std::make_pair(module_id, channel_id);
                if (BB7_FEBEX_Map.find(idx) != BB7_FEBEX_Map.end())
                {
                    Sum_Time[Hits] = tmp_Sum_Time;
                    this->pdata++;
                    
                    FEBEX_TS* Channel_Time = (FEBEX_TS*) this->pdata;
                    Chan_Time[Hits] = ((Channel_Time->chan_ts) + (tmp_ChanTime_hi << 32)) * 10; // convert to ns
                    this->pdata++;

                    FEBEX_En* Channel_Energy = (FEBEX_En*) this->pdata;
                    Chan_Energy[Hits] = Channel_Energy->chan_en;
                    Chan_CF[Hits] = 10.0 * ((Channel_Time->chan_ts) + (Channel_Energy->cf) / 64.0);

                    if (Channel_Energy->chan_en & 0x00800000)
                    {
                        int energy = 0xFF000000 | Channel_Energy->chan_en;
                        Chan_Energy[Hits] = energy;
                    }

                    Pileup[Hits] = Channel_Energy->pileup != 0; // CEJ: why does this need to be a condition...
                    Overflow[Hits] = Channel_Energy->overflow != 0;
                    Side[Hits] = BB7_FEBEX_Map[idx].first;
                    Strip[Hits] = BB7_FEBEX_Map[idx].second;
                    this->pdata++;

                    Hits++;
                    
                } // mapping loop
                else
                {
                    this->pdata += 3;
                }

            } // channel loop
            
            num_modules--;
        } // F0 header

        if (num_modules != 0)
        {
            this->pdata++;
            SumChannel_Head = (FEBEX_Header*) this->pdata;
        }
        else FEBEX_data_loop = false;
    }
}

void BB7_FEBEX_Detector_System::reset_fired_channels()
{   

    Hits = 0;
    for (int i = 0; i < max_hits; i++)
    {
        Side[i] = 0;
        Strip[i] = 0;
        Sum_Time[i] = -1; // CEJ: why is this -1?
        Chan_Time[i] = 0;
        Chan_Energy[i] = 0;
        Chan_CF[i] = 0;
        Pileup[i] = -1;
        Overflow[i] = -1;
    }

}

int* BB7_FEBEX_Detector_System::get_pdata() { return pdata; }