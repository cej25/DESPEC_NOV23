#include "BB7_TWINPEAKS_Event_Store.h"
#include <iostream>

void BB7_TWINPEAKS_Cluster::AddEvent(BB7_TWINPEAKS_Event const& event)
{   

    // energy comes from ToTs, Time is epoch+coarse-fine (FAST LEAD)
    Energy += event.Energy;
    if (event.Strip < StripMin) StripMin = event.Strip;
    if (event.Strip > StripMax) StripMax = event.Strip;
    if (event.Time < TimeMin) TimeMin = event.Time;
    if (event.Time > TimeMax) TimeMax = event.Time;
    StripSum += event.Strip;
    Strip = (double) StripSum / ++N;
    Time = TimeMin;

}

void BB7_TWINPEAKS_Cluster::AddCluster(BB7_TWINPEAKS_Cluster const& cluster)
{
    if (cluster.StripMin < StripMin) StripMin = cluster.Strip;
    if (cluster.StripMax > StripMax) StripMax = cluster.Strip;
    if (cluster.Time < TimeMin) TimeMin = cluster.Time;
    if (cluster.Time > TimeMax) TimeMax = cluster.Time;
    Energy += cluster.Energy;
    StripSum += cluster.StripSum;
    N += cluster.N;
    Strip = (double) StripSum / N;
    Time = TimeMin;
}

bool BB7_TWINPEAKS_Cluster::IsAdjacent(BB7_TWINPEAKS_Event const& event) const
{
    if (event.Side != Side) return false;
    if (event.Strip >= Strip - 1 && event.Strip <= StripMax + 1) return true;
    return false;
}

bool BB7_TWINPEAKS_Cluster::IsGoodTime(BB7_TWINPEAKS_Event const& event, int window) const
{
    if (event.Time >= TimeMin - window && event.Time <= TimeMax + window) return true;
    return false;
}

bool BB7_TWINPEAKS_Cluster::IsGoodTime(BB7_TWINPEAKS_Cluster const& cluster, int window) const
{
    if (cluster.TimeMin >= TimeMin - window && cluster.TimeMin <= TimeMax + window) return true;
    if (cluster.TimeMax >= TimeMin - window && cluster.TimeMax <= TimeMax + window) return true;
    return false;
}