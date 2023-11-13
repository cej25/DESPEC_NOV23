#include "BB7_FEBEX_Event_Store.h"
#include <iostream>

void BB7_FEBEX_Cluster::AddEvent(BB7_FEBEX_Event const& event)
{
    // if SIDE/STRIP == -1?

    Energy += event.Energy;

    if (event.Strip < StripMin) StripMin = event.Strip;
    if (event.Strip > StripMax) StripMax = event.Strip;
    if (event.Time < TimeMin) TimeMin = event.Time;
    if (event.Time > TimeMax) TimeMax = event.Time;
    StripSum += event.Strip;
    Strip = (double) StripSum / ++N;
    Time = TimeMin;
}

void BB7_FEBEX_Cluster::AddCluster(BB7_FEBEX_Cluster const& cluster)
{   
    // if SIDE/STRIP == -1?

    if (cluster.StripMin < StripMin) StripMin = cluster.StripMin;
    if (cluster.StripMax > StripMax) StripMax = cluster.StripMax;
    if (cluster.Time < TimeMin) TimeMin = cluster.Time;
    if (cluster.Time > TimeMax) TimeMax = cluster.Time;
    Energy += cluster.Energy;
    StripSum += cluster.StripSum;
    N += cluster.N;
    Strip = (double) StripSum / N;
    Time = TimeMin;

}

bool BB7_FEBEX_Cluster::IsAdjacent(BB7_FEBEX_Event const& event) const
{
    // skip SIDE/STRIP == -1?
    if (event.Side != Side) return false;
    if (event.Strip >= StripMin - 1 && event.Strip <= StripMax + 1) return true;
    return false;
}

bool BB7_FEBEX_Cluster::IsGoodTime(BB7_FEBEX_Cluster const& cluster, int window) const
{
    // skip SIDE/STRIP == -1?
    if (cluster.TimeMin >= TimeMin - window && cluster.TimeMin <= TimeMax + window) return true;
    if (cluster.TimeMax >= TimeMin - window && cluster.TimeMax <= TimeMax + window) return true;
    return false;
}

