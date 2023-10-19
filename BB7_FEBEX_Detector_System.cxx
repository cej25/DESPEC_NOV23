#include "BB7_FEBEX_Detector_System.h"

#include <cstdlib>
#include <map>

#include "FEBEX.h"
#include "Configuration_Files/DESPEC_General_Setup/DESPEC_Setup_File.h"

// using namespace std;

BB7_FEBEX_Detector_System::BB7_FEBEX_Detector_System()
{
    // set amount of detectors
    max_am_dets = BB7_MAX_HITS;

    fired_FEBEX_amount = 0;

    Sum_Time = new ULong64_t[max_am_dets];
    Hit_Pattern = new int[max_am_dets];

    // these names probably have to change
    det_ids = new int[max_am_dets];
    crystal_ids = new int[max_am_dets];

    Chan_Time = new ULong64_t[max_am_dets];
    Chan_Energy = new double[max_am_dets];
    Chan_CF = new ULong64_t[max_am_dets];
    Pileup = new bool[max_am_dets];
    Overflow = new bool[max_am_dets];

    BB7_E_CALIB = new BB7_Energy_Calibration();
    BB7_T_CALIB = new BB7_Time_Calibration();

    load_board_channel_file();

}

BB7_FEBEX_Detector_System::~BB7_FEBEX_Detector_System()
{
    BB7_Map.clear(); // not necessary?
    delete[] det_ids;
    delete[] crystal_ids;
    delete[] Sum_Time;
    delete[] Hit_Pattern;
    delete[] Pileup;
    delete[] Overflow;
    delete[] Chan_Time;
    delete[] Chan_Energy;
    delete[] Chan_CF;
    delete[] BB7_E_CALIB;
    delete[] BB7_T_CALIB;
}

void BB7_FEBEX_Detector_System::load_board_channel_file()
{
    // do loading
}

void BB7_FEBEX_Detector_System::get_Event_Data(Raw_Event* RAW)
{
    RAW->set_DATA_BB7(fired_FEBEX_amount, Sum_Time, BB7_channels, Chan_Time, Chan_Energy, Chan_CF, det_ids, crystal_ids, Pileup, Overflow);
}

void BB7_FEBEX_Detector_System::Process_MBS(int* pdata)
{
    reset_fired_channels();

    std::pair<int, int> current_det;

    this->pdata = pdata; // god i hate this
    bool FEBEX_data_loop = true;

    int num_modules = BB7_FEBEX_MODULES; 
    
    fired_FEBEX_amount = 0; // how would this not already be zero.. 

    // loop through padding
    FEBEX_Add* FEBEX_add = (FEBEX_Add*) this->pdata;
    while (FEBEX_add->add == 0xADD)
    {
        this->pdata++;
        FEBEX_add = (FEBEX_Add*) this->pdata;
    }

    FEBEX_Header* SumChannel_Head = (FEBEX_Header*) this->pdata;

    while (FEBEX_data_loop)
    {
        if (SumChannel_Head->ff == 0xFF)
        {
            board_id = SumChannel_Head->chan_head;
            this->pdata++;

            FEBEX_Chan_Size* Channel_Size = (FEBEX_Chan_Size*) this->pdata;
            num_channels = ((Channel_Size->chan_size) / 4) - 1;
            if (num_channels == 0) num_modules--;
            this->pdata++;

            FEBEX_Half_Time* EventTime_Hi = (FEBEX_Half_Time*) this->pdata;
            this->pdata++;

            FEBEX_Evt_Time* EventTime_Lo = (FEBEX_Evt_Time*) this->pdata;
            
            tmp_Sum_Time = (EventTime_Lo->evt_time) | (EventTime_Hi->ext_time << 32);
            this->pdata++;

            FEBEX_Flag_Hits* Flags = (FEBEX_Flag_Hits*) this->pdata;
            tmp_Pileup = Flags->pile_flags;
            tmp_Hit_Pattern = Flags->hit_pattern;

            for (int j = 15; j >= 0; j--)
            {
                if (tmp_Pileup & (1 << j))
                {
                    pileup_flags[j] = 1;
                }
                if (tmp_Hit_Pattern & (1 << j))
                {
                    BB7_channels[j] = j;
                    num_channels_fired++;
                }
            }
            this->pdata++;

        } // FF header
        else if (SumChannel_Head->ff == 0xF0)
        {
            this->pdata--; // move back to DEADBEEF for this loop to work

            for (int i = 0; i < num_channels; i++)
            {
                this->pdata++;

                FEBEX_Chan_Header* Channel_Head = (FEBEX_Chan_Head*) this->pdata;
                int tmp_Ch_ID = Channel_Head->Ch_ID;

                // CEJ: is this necessary here?
                auto idx = std::make_pair(board_id, tmp_Ch_ID);
                if (BB7_Map.find(idx) != BB7_Map.end())
                {
                    Sum_Time[fired_FEBEX_amount] = tmp_Sum_Time;
                    this->pdata++;
                    
                    FEBEX_TS* Channel_Time = (FEBEX_TS*) this->pdata;
                    Chan_Time[fired_FEBEX_amount] = ((Channel_Time->chan_ts) | (Channel_Head->ext_chan_ts << 32)) * 10; // convert to ns
                    this->pdata++;

                    FEBEX_En* Channel_Energy = (FEBEX_En*) this->pdata;
                    Chan_Energy[fired_FEBEX_amount] = Channel_Energy->chan_en;
                    Chan_CF[fired_FEBEX_amount] = 10.0 * ((Channel_Time->chan_ts) + (Channel_Energy->cf) / 64.0);

                    if (Channel_Energy->chan_en & 0x00800000)
                    {
                        int energy = 0xFF000000 | Channel_Energy->chan_en;
                        Chan_Energy[fired_FEBEX_amount] = energy;
                    }

                    Pileup[fired_FEBEX_amount] = Channel_Energy->pileup != 0; // CEJ: why does this need to be a condition...
                    Overflow[fired_FEBEX_amount] = Channel_Energy->overflow != 0;
                    det_ids[fired_FEBEX_amount] = BB7_Map[idx].first;
                    crystal_ids[fired_FEBEX_amount] = BB7_Map[idx].second;
                    this->pdata++;

                    fired_FEBEX_amount++;
                    
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
    fired_FEBEX_amount = 0;
    num_channels_fired = 0;

    for (int i = 0; i < max_am_dets; i++)
    {
        Sum_Time[i] = -1;
        pileup_flags[i] = -1;
        BB7_channels[i] = 0;
        Pileup[i] = -1;
        Hit_Pattern[i] = 0;
        Chan_Time[i] = 0;
        Chan_Energy[i] = 0;
        Chan_CF[i] = 0;
    }
}

int* BB7_FEBEX_Detector_System::get_pdata() { return pdata; }