#include "TAidaConfiguration.h"

#include <algorithm>
#include <fstream>
#include <ios>
#include <iostream>
#include <locale>
#include <limits>
#include <sstream>
#include <string>

TAidaConfiguration* TAidaConfiguration::instance = nullptr;

TAidaConfiguration::TAidaConfiguration(std::string path) :
    fees(0), dssds(0), wide(false), adjustadc(false), useucesb(false),
    ignorembsts(false), stats(false), ucesbshift(0), eventwindow(2000)
{
  ReadConfiguration(path);
  DSSDtoFEE();
}

inline DSSDSide ParseSide(std::string arg)
{
  std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
  if (arg == "junction") return DSSDSide::Junction;
  return DSSDSide::Ohmic;
}

void TAidaConfiguration::ReadConfiguration(std::string path)
{
  fbwindow = std::numeric_limits<double>::max();
  fbenergyh = std::numeric_limits<double>::max();
  fbenergyl = std::numeric_limits<double>::max();

  std::ifstream cfg(path);
  constexpr auto ignore = std::numeric_limits<std::streamsize>::max();
  int sub_DSSD = -1;
  bool sub_Scaler = false;
  bool sub_Analysis = false;
  while (cfg)
  {
    if (cfg.peek() == '#')
    {
      cfg.ignore(ignore, '\n');
      continue;
    }

    std::string line_s;
    std::getline(cfg, line_s);
    std::istringstream line(line_s);

    bool sub = false;
    if (line.peek() == '-')
    {
      sub = true;
      line.get();
    }

    std::string option;
    std::getline(line, option, ':');
    line.get();

    std::transform(option.begin(), option.end(), option.begin(), ::tolower);
    option.erase(option.find_last_not_of(" \n\r\t") + 1);
    option.erase(0, option.find_first_not_of(" \n\r\t"));

    if (option == "fees")
    {
      line >> fees;
      fee.resize(fees);
      for (FEEConfiguration& f: fee)
      {
        f.DSSD = -1;
      }
    }
    else if (option == "dssds")
    {
      line >> dssds;
      dssd.resize(dssds);
      for (DSSDConfiguration& d : dssd)
      {
        d.DSSD = -1;
        d.MEC = false;
      }
    }
    else if (option == "wide")
    {
      line >> std::boolalpha >> wide;
    }
    else if (option == "ignorembsts")
    {
      line >> std::boolalpha >> ignorembsts;
    }
    else if (option == "ucesb")
    {
      line >> std::boolalpha >> useucesb;
    }
    else if (option == "stats")
    {
      line >> std::boolalpha >> stats;
    }
    else if (option == "ucesbshift")
    {
      line >> ucesbshift;
    }
    else if (option == "eventwindow")
    {
      line >> eventwindow;
    }
    else if (option == "frontbackwindow")
    {
      line >> fbwindow;
    }
    else if (option == "frontbackenergyh")
    {
      line >> fbenergyh;
    }
    else if (option == "frontbackenergyl")
    {
      line >> fbenergyl;
    }
    else if (option == "dssd")
    {
      line >> sub_DSSD;
      dssd[sub_DSSD - 1].DSSD = sub_DSSD;
    }
    else if (option == "top" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].Top;
    }
    else if (option == "bottom" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].Bottom;
    }
    else if (option == "left" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].Left;
    }
    else if (option == "right" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].Right;
    }
    else if (option == "leftleft" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].Left;
    }
    else if (option == "leftright" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].LeftRight;
    }
    else if (option == "centreleft" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].CentreLeft;
    }
    else if (option == "centreright" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].CentreRight;
    }
    else if (option == "rightleft" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].RightLeft;
    }
    else if (option == "rightright" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].Right;
    }
    else if (option == "x" && sub && sub_DSSD > 0)
    {
      std::string arg;
      line >> arg;
      dssd[sub_DSSD - 1].XSide = ParseSide(arg);
    }
    else if (option == "y" && sub && sub_DSSD > 0)
    {
      std::string arg;
      line >> arg;
      dssd[sub_DSSD - 1].YSide = ParseSide(arg);
    }
    else if (option == "mec" && sub && sub_DSSD > 0)
    {
      bool mec = false;
      line >> mec;
      dssd[sub_DSSD - 1].MEC = mec;
    }
    else if (option == "scalers")
    {
      sub_Scaler = true;
      sub_Analysis = false;
    }
    else if (sub && sub_Scaler)
    {
      std::string arg;
      std::getline(line, arg);
      int idx = std::strtol(option.c_str(), NULL, 0);
      scalers[idx] = arg;
    }
    else if (option == "analysis")
    {
      sub_Analysis = true;
      sub_Scaler= false;
    }
    else if (option == "reducenoise" && sub && sub_Analysis)
    {
      line >> std::boolalpha >> reducenoise;
    }
    else if (option == "clusterimpants" && sub && sub_Analysis)
    {
      line >> std::boolalpha >> clusterimpants;
    }
    else if (option == "clusterdecays" && sub && sub_Analysis)
    {
      line >> std::boolalpha >> clusterdecays;
    }
    else if (option == "calibrate" && sub && sub_Analysis)
    {
      line >> std::boolalpha >> calibrate;
    }
    else if (option == "parallelcalibrate" && sub && sub_Analysis)
    {
      line >> std::boolalpha >> parallelcalibrate;
    }
    else if (option == "hugethreshold" && sub && sub_Analysis)
    {
      line >> hugethreshold;
    }
    else if (option == "pulserthreshold" && sub && sub_Analysis)
    {
      line >> pulserthreshold;
    }
  }

  if (useucesb && ignorembsts)
  {
    std::cout << "AIDA Configuration Warning: Not ignoring MBS timestamps when ucesb is used" << std::endl;
    ignorembsts = false;
  }

  std::cout << "/////////////////////////////////////////////////////" << std::endl;
  std::cout << "AIDA Configuration: " << fees << " FEEs, " << dssds << " DSSDs, "
    << scalers.size() << " Scalers" << std::endl;

  std::cout << "AIDA Options: ";
  if (ignorembsts) std::cout << "NoMBS ";
  else std::cout << "MBS ";
  if (wide) std::cout << "wide ";
  if (useucesb) std::cout << "ucesb ";
  if (stats) std::cout << "stats ";
  std::cout << std::endl;
  if (useucesb && ucesbshift) std::cout << "ucesb Timestamps are shifted by " << ucesbshift << " ns" << std::endl;

  std::cout << "AIDA Windows: Event: " << eventwindow << " ns, Front/Back: " << fbwindow << " ns" << std::endl;
  std::cout << "AIDA Gates: Front/Back High: " << fbenergyh << " MeV, Low: " << fbenergyl << " keV" << std::endl;

  std::cout << "Analysis Options: ";
  if (reducenoise) std::cout << "ReduceNoise ";
  if (clusterimpants && clusterdecays) std::cout << "ClusterImplantsDecays ";
  if (clusterimpants && !clusterdecays) std::cout << "ClusterImplants";
  if (!clusterimpants && clusterdecays) std::cout << "ClusterDecays ";
  if (calibrate && parallelcalibrate) std::cout << "ParallelCalibrate ";
  if (calibrate && !parallelcalibrate) std::cout << "Calibrate ";
  std::cout << std::endl;
  std::cout << "Analysis Thresholds: Nonsense: " << hugethreshold << ", Pulser: " << pulserthreshold << std::endl;
  std::cout << "/////////////////////////////////////////////////////" << std::endl;
}

void TAidaConfiguration::DSSDtoFEE()
{
  for (DSSDConfiguration& d : dssd)
  {
    fee[d.Top-1].DSSD = d.DSSD;
    fee[d.Top-1].High = true;
    fee[d.Top-1].Side = d.YSide;

    fee[d.Right-1].DSSD = d.DSSD;
    fee[d.Right-1].High = true;
    fee[d.Right-1].Side = d.XSide;

    fee[d.Bottom-1].DSSD = d.DSSD;
    fee[d.Bottom-1].High = false;
    fee[d.Bottom-1].Side = d.YSide;

    fee[d.Left-1].DSSD = d.DSSD;
    fee[d.Left-1].High = false;
    fee[d.Left-1].Side = d.XSide;

    if (!wide) continue;
    fee[d.Left-1].Segment = WideAIDASegment::Left;

    fee[d.LeftRight-1].DSSD = d.DSSD;
    fee[d.LeftRight-1].High = true;
    fee[d.LeftRight-1].Side = d.XSide;
    fee[d.LeftRight-1].Segment = WideAIDASegment::Left;

    fee[d.CentreLeft-1].DSSD = d.DSSD;
    fee[d.CentreLeft-1].High = false;
    fee[d.CentreLeft-1].Side = d.XSide;
    fee[d.CentreLeft-1].Segment = WideAIDASegment::Centre;

    fee[d.CentreRight-1].DSSD = d.DSSD;
    fee[d.CentreRight-1].High = true;
    fee[d.CentreRight-1].Side = d.XSide;
    fee[d.CentreRight-1].Segment = WideAIDASegment::Centre;

    fee[d.RightLeft-1].DSSD = d.DSSD;
    fee[d.RightLeft-1].High = false;
    fee[d.RightLeft-1].Side = d.XSide;
    fee[d.RightLeft-1].Segment = WideAIDASegment::Right;

    fee[d.Right-1].Segment = WideAIDASegment::Right;
  }
}
