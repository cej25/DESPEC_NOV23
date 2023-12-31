#ifndef AIDA_ANL_CONFIG
#define AIDA_ANL_CONFIG

#include <iostream>
#include <map>
#include <string>
#include <vector>

enum DSSDSide
{
  Junction = -1,
  Ohmic = 1,
};

enum WideAIDASegment
{
  Left,
  Centre,
  Right
};

struct DSSDConfiguration
{
  int DSSD;
  int Top;
  int Bottom;
  int Left;
  int Right;
  // Wide AIDA only mappings
  int LeftRight;
  int CentreLeft;
  int CentreRight;
  int RightLeft;
  // Side mapping
  DSSDSide XSide;
  DSSDSide YSide;
  // MEC
  bool MEC;
};

struct FEEConfiguration
{
  int DSSD;
  DSSDSide Side;
  bool High;
  // Wide AIDA only data
  WideAIDASegment Segment;
};

class TAidaConfiguration
{
public:
    static TAidaConfiguration const* GetInstance();
    static void Create(std::string path);

    int FEEs() const;
    int DSSDs() const;
    bool Wide() const;

    bool AdjustADC() const;
    bool ucesb() const;
    bool IgnoreMBSTS() const;
    bool ShowStats() const;
    int ucesbShift() const;

    double EventWindow() const;
    double FrontBackWindow() const;
    double FrontBackEnergyH() const;
    double FrontBackEnergyL() const;

    bool ReduceNoise() const;
    bool ClusterImplants() const;
    bool ClusterDecays() const;
    bool Calibrate() const;
    bool ParallelCalibrate() const;
    int HugeThreshold() const;
    int PulserThreshold() const;

    DSSDConfiguration DSSD(int i) const;
    FEEConfiguration FEE(int i) const;
    std::string Scaler(int i) const;
    std::map<int, std::string> const& ScalerMap() const;

private:
    TAidaConfiguration(std::string path);
    void ReadConfiguration(std::string path);
    void DSSDtoFEE();

    static TAidaConfiguration* instance;

    int fees;
    int dssds;
    bool wide;
    bool adjustadc;
    bool useucesb;
    bool ignorembsts;
    bool stats;
    int ucesbshift;
    double eventwindow;
    double fbwindow;
    double fbenergyh;
    double fbenergyl;

    // analysis options
    bool reducenoise;
    bool clusterimpants;
    bool clusterdecays;
    bool calibrate;
    bool parallelcalibrate;
    int hugethreshold;
    int pulserthreshold;

    std::vector<DSSDConfiguration> dssd;
    std::vector<FEEConfiguration> fee;
    std::map<int, std::string> scalers;
};

inline TAidaConfiguration const* TAidaConfiguration::GetInstance()
{
  if (!instance)
  {
    std::cout << "DESPEC Analysis: Creating AIDA Configuration" << std::endl;
    TAidaConfiguration::Create("Configuration_Files/AIDA/AIDA.txt");
  }
  return instance;
}

inline void TAidaConfiguration::Create(std::string path)
{
  delete instance;
  instance = new TAidaConfiguration(path);
}

inline int TAidaConfiguration::FEEs() const
{
  return fees;
}

inline int TAidaConfiguration::DSSDs() const
{
  return dssds;
}

inline bool TAidaConfiguration::Wide() const
{
  return wide;
}

inline bool TAidaConfiguration::AdjustADC() const
{
  return adjustadc;
}

inline bool TAidaConfiguration::IgnoreMBSTS() const
{
  return ignorembsts;
}

inline bool TAidaConfiguration::ucesb() const
{
  return useucesb;
}

inline bool TAidaConfiguration::ShowStats() const
{
  return stats;
}

inline int TAidaConfiguration::ucesbShift() const
{
  return ucesbshift;
}

inline double TAidaConfiguration::EventWindow() const
{
  return eventwindow;
}

inline double TAidaConfiguration::FrontBackWindow() const
{
  return fbwindow;
}

inline double TAidaConfiguration::FrontBackEnergyH() const
{
  return fbenergyh;
}

inline double TAidaConfiguration::FrontBackEnergyL() const
{
  return fbenergyl;
}

inline bool TAidaConfiguration::ReduceNoise() const
{
  return reducenoise;
}

inline bool TAidaConfiguration::ClusterImplants() const
{
  return clusterimpants;
}

inline bool TAidaConfiguration::ClusterDecays() const
{
  return clusterdecays;
}

inline bool TAidaConfiguration::Calibrate() const
{
  return calibrate;
}

inline bool TAidaConfiguration::ParallelCalibrate() const
{
  return parallelcalibrate;
}

inline int TAidaConfiguration::HugeThreshold() const
{
  return hugethreshold;
}

inline int TAidaConfiguration::PulserThreshold() const
{
  return pulserthreshold;
}

inline DSSDConfiguration TAidaConfiguration::DSSD(int i) const
{
  return dssd[i];
}

inline FEEConfiguration TAidaConfiguration::FEE(int i) const
{
  return fee[i];
}

inline std::string TAidaConfiguration::Scaler(int i) const
{
  if (scalers.find(i) != scalers.end())
  {
    return scalers.at(i);
  }
  else
  {
    return "";
  }
}

inline std::map<int, std::string> const& TAidaConfiguration::ScalerMap() const
{
  return scalers;
}

#endif /* AIDA_ANL_CONFIG */
