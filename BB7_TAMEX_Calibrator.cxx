#include "BB7_TAMEX_Calibrator.h"

//using namespace std;

BB7_TAMEX_Calibrator::BB7_TAMEX_Calibrator(bool ONLINE)
{
    this->ONLINE = ONLINE;

    nbins = 600;
    min_val = 0;
    max_val = 600;

    // only for online calibration
    if (this->ONLINE)
    {
        fired = new bool*[100];
        for (int i = 0; i < 100; i++)
        {
            fired[i] = new bool[100];
            for (int j = 0; j < 100; j++)
            {
                fired[i][j] = false;
            }
        }
        char tmp_name[1000];

        Fine_Hist = new TH1D**[100];
        for (int i = 0; i < 100; i++)
        {
            Fine_Hist[i] = new TH1D*[100];
            for (int j = 0; j < 100; j++)
            {
                sprintf(tmp_name, "PDF_%d_%d", i, j);
                Fine_Hist[i][j] = new TH1D(tmp_name, tmp_name, nbins, min_val, max_val);
            }
        }
    }
    else
    {
        bins_x_arr = new double[nbins];
        Cal_arr = new double**[100];
        for (int i = 0; i < 100; i++)
        {
            Cal_arr[i] = new double*[100];
            for (int j = 0; j < 100; j++)
            {
                Cal_arr[i][j] = new double[nbins]; 
            }
        }
        fired = NULL;
        Fine_Hist = NULL;
        load_Calibration_Files();
    }
}

BB7_TAMEX_Calibrator::~BB7_TAMEX_Calibrator()
{
    if (ONLINE)
    {
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                delete Fine_Hist[i][j];
            }
            delete[] fired[i];
            delete[] Fine_Hist[i];
        }
        delete fired;
        delete Fine_Hist;
    }
    else
    {
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                if (Cal_arr[i][j])
                {
                    delete[] Cal_arr[i][j];
                }
            }
            delete[] Cal_arr[i];
            delete[] wired_tamex_ch[i];
        }
        delete[] wired_tamex_ch;
        delete[] Cal_arr;
        delete[] bins_x_arr;
    }
}

void BB7_TAMEX_Calibrator::load_Calibration_Files()
{
    // load files
    std::ifstream map_file("Configuration_Files/BB7/Calibration_BB7_TAMEX/MAP.dat");
    
    std::string line;

    if (map_file.fail())
    {
        std::cerr << "Could not find BB7_TAMEX Calibration file MAP" << std::endl;
        exit(0);
    }

    const char* format_MAP = "%d %d";
    int tamex_id, ch_id;

    int used_ids[1000][100];
    iter = 0;

    // CEJ: this 100 must be a variable somewhere
    wired_tamex_ch = new bool*[100];
    for (int i = 0; i < 100; i++)
    {
        wired_tamex_ch[i] = new bool[100];
        for (int j = 0; j < 100; j++) wired_tamex_ch[i][j] = false;
    }

    while (map_file.good())
    {
        getline(map_file, line, '\n');
        if (line[0] == '#') continue;
        sscanf(line.c_str(), format_MAP, &tamex_id, &ch_id);
        used_ids[iter][0] = tamex_id;
        used_ids[iter][1] = ch_id;

        wired_tamex_ch[tamex_id][ch_id] = true;

        iter++;
    }

    // Load wired calibration files specified by MAP
    char filename[1000];
    std::ifstream file;

    int b_iter = 0;
    double bin, val;

    const char* format = "%lf %lf";
    bool first = true;

    for (int i = 0; i < iter; i++)
    {
        tamex_id = used_ids[i][0];
        ch_id = used_ids[i][1];

        b_iter = 0;

        sprintf(filename, "Configuration_Files/BB7/Calibration_BB7_TAMEX/Calib_%d_%d.dat", tamex_id, ch_id);
        file.open(filename);

        if (file.fail())
        {
            std::cerr << "Could not find BB7 TAMEX Calibration file " << tamex_id << " " << ch_id << std::endl;
            exit(0); 
        }

        while (file.good())
        {
            getline(file, line, '\n');
            if (line[0] == '#') continue;
            sscanf(line.c_str(), format, &bin, &val);
            if (first) bins_x_arr[b_iter] = bin;
            Cal_arr[tamex_id][ch_id][b_iter] = val;
            b_iter++;
        }

        first = false;
        file.close();
        file.clear();
        
    }

}

double BB7_TAMEX_Calibrator::get_Calibration_val(double value, int tamex_id_tmp, int ch_id_tmp)
{
    // get calibration val
    double return_val = 0;
    double value_t = (double) value;
    double tmp, tmp2;

    for (int i = 0; i < nbins; i++)
    {   
        if (ch_id_tmp > -1 && ch_id_tmp < 65)
        {
            tmp = Cal_arr[tamex_id_tmp][ch_id_tmp][i];
            tmp2 = Cal_arr[tamex_id_tmp][ch_id_tmp][i + 1];
            if (value >= bins_x_arr[i] && value < bins_x_arr[i + 1])
            {
                return_val = (tmp2 - tmp) / (bins_x_arr[i + 1] - bins_x_arr[i]) * ((value_t - bins_x_arr[i + 1]) + rand() % 1000 * 0.001) + tmp;
                break;
            }
        }
    }
    return return_val;
}

void BB7_TAMEX_Calibrator::get_data(double** fine_T, UInt** ch_id, int tamex_iter, int* iterator)
{
    // write into corresponding root histograms
    for (int i = 0; i < tamex_iter; i++)
    {
        for (int j = 0; j < iterator[i]; j++)
        {   
            // CEJ does this 9 need to change...be careful
            if (i < 9 && ch_id[i][j] < 66)
            {
                Fine_Hist[i][ch_id[i][j]]->Fill(fine_T[i][j]);
                if (j % 2 == 1) fired[i][ch_id[i][j]] = true;
            }
        }
    }
}

void BB7_TAMEX_Calibrator::ONLINE_CALIBRATION()
{
    // online calibration
    std::ofstream cal_file;
    std::ofstream map_file("Configureation_Files/BB7/Calibration_BB7_TAMEX/MAP.dat");
    map_file << "#BB7_TAMEX Calibration Map" << std::endl;
    map_file << "#Map of used Tamex IDs and their channels (if stated, used = true" << std::endl;
    map_file << "#" << std::endl;
    map_file << "#tamex ids (0 or 1) vs Channel Num." << std::endl;
    map_file << "#" << std::endl;

    std::cout << "ONLINE CALIBRATION for BB7 TWINPEAKS initialised" << std::endl;

    char filename[1000];

    double sum_arr[nbins];
    double full_sum = 0;
    std::cout << "running... " << std::endl;
    std::cout.flush();

    int max_bin = 0;

    double bins_x[nbins], val = 0;
    for (int i = 0; i < nbins; i++) bins_x[i] = (max_val - min_val) / ((double) nbins) * (i + 1);

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {   
            
            if (fired[i][j])
            {   
                sprintf(filename, "Configuration_Files/BB7/Calibration_BB7_TAMEX/Calib_%d_%d.dat", i, j);
                cal_file.open(filename);

                if (cal_file.fail())
                {
                    std::cerr << "Could not open " << filename << std::endl;
                    exit(0);
                }

                map_file << i << "\t" << j << std::endl;

                cal_file << "# Calibration file of tamex_id" << i << " @ channel " << j << std::endl;
                cal_file << "# fine_T bin\t\t Calibration value" << std::endl;

                sum_arr[0] = Fine_Hist[i][j]->GetBinContent(1);
                
                for (int k = 1; k < nbins; k++)
                {
                    sum_arr[k] = Fine_Hist[i][j]->GetBinContent(k + 1) + sum_arr[k - 1];
                    if (Fine_Hist[i][j]->GetBinContent(k + 1) > 0) max_bin = k;
                }

                full_sum = sum_arr[nbins - 1];
                double default_value = 0;

                for (int k = 0; k < nbins; k++)
                {
                    if (val > 0) default_value = 1;
                    val = (k < max_bin) ? ((double)(sum_arr[k])) : default_value;
                    cal_file << bins_x[k] << "\t\t" << val << std::endl;
                }

                cal_file.close();
                cal_file.clear();
            }
        }

        std::cout << "\r";
        std::cout << "running... " << i << " % \t\t\t\t";
        std::cout.flush();
    }

    std::cout << "\r";
    std::cout << "running... DONE" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::cout << "Exiting program after Calibration. Run again to use new calibration." << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;

    map_file.close();
    
}

