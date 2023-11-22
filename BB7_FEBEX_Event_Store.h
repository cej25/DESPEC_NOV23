#ifndef BB7_FEBEX_EVENT_STORE_H
#define BB7_FEBEX_EVENT_STORE_H

#include "TGo4EventElement.h"

class BB7_FEBEX_Event : public TObject
{
    public:

        int Side;
        int Strip;
        double Energy;
        int64_t Time;

        int64_t CF;
        bool Pileup;
        bool Overflow;

        // CF, PILEUP, OVERFLOW

        BB7_FEBEX_Event();
        void Zero();
        virtual ~BB7_FEBEX_Event() {}; 

        ClassDef(BB7_FEBEX_Event, 1);

};

class BB7_FEBEX_Cluster : public TObject
{
    public:
        int Side;
        double Energy;
        double Strip;
        int64_t Time;
        int N;
        // CF, PILEUP, OVERFLOW etc

        BB7_FEBEX_Cluster() { Zero(); }
        void Zero();
        ~BB7_FEBEX_Cluster() {}
        
        void AddEvent(BB7_FEBEX_Event const& event);
        void AddCluster(BB7_FEBEX_Cluster const& cluster);
        bool IsAdjacent(BB7_FEBEX_Event const& event) const;
        bool IsGoodTime(BB7_FEBEX_Event const& event, int window = 2000) const;
        bool IsGoodTime(BB7_FEBEX_Cluster const& cluster, int window) const;

        int StripMin;
        int StripMax;
        int64_t TimeMin;
        int64_t TimeMax;
        int StripSum;

};

class BB7_FEBEX_Hit : public TObject
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

        // cluster size for correlations
        int StripXMin;
        int StripXMax;
        int StripYMin;
        int StripYMax;
        int ClusterSizeX;
        int ClusterSizeY;

        int64_t Time;
        int64_t TimeFront;
        int64_t TimeBack;
        
        BB7_FEBEX_Hit() { Zero(); };
        void Zero();
        virtual ~BB7_FEBEX_Hit() {};

        ClassDef(BB7_FEBEX_Hit, 3)
};

#endif