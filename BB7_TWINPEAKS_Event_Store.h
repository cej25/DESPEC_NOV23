#ifndef BB7_TWINPEAKS_EVENT_STORE_H
#define BB7_TWINPEAKS_EVENT_STORE_H

#include "TGo4EventElement.h"


class BB7_TWINPEAKS_Event : public TObject
{
    public:
        int Side;
        int Strip;
        double Energy;
        int64_t Time;

        BB7_TWINPEAKS_Event();
        void Zero();
        virtual ~BB7_TWINPEAKS_Event() {};

        ClassDef(BB7_TWINPEAKS_Event, 1);
};

class BB7_TWINPEAKS_Cluster : public TObject
{
    public:
        int Side;
        double Energy;
        double Strip;
        int64_t Time;
        int N;
        // Time with epoch, coarse time, fine time etc

        BB7_TWINPEAKS_Cluster() { Zero(); }
        void Zero();
        ~BB7_TWINPEAKS_Cluster() {}

        void AddEvent(BB7_TWINPEAKS_Event const& event);
        void AddCluster(BB7_TWINPEAKS_Cluster const& cluster);
        bool IsAdjacent(BB7_TWINPEAKS_Event const& event) const;
        bool IsGoodTime(BB7_TWINPEAKS_Event const& event, int window = 2000) const;
        bool IsGoodTime(BB7_TWINPEAKS_Cluster const& event, int window) const;
        
        int StripMin;
        int StripMax;
        int64_t TimeMin;
        int64_t TimeMax;
        int StripSum;
        
};

class BB7_TWINPEAKS_Hit : public TObject
{
    public:
        int Event;

        double StripX;
        double StripY;
        double PosX;
        double PosY;

        double Energy;
        double EnergyFront;
        double EnergyBack;

        int StripXMin;
        int StripXMax;
        int StripYMin;
        int StripYMax;
        int ClusterSizeX;
        int ClusterSizeY;
        
        int64_t Time;
        int64_t TimeFront;
        int64_t TimeBack;

        BB7_TWINPEAKS_Hit() { Zero(); }
        void Zero();
        virtual ~BB7_TWINPEAKS_Hit() {};

        ClassDef(BB7_TWINPEAKS_Hit, 1);
};

#endif 