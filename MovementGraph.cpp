#include "MovementGraph.h"

#include <algorithm> // Per find

std::list<std::list<Track>> MovementGraph::get_feasable_path()
{
    return std::list<std::list<Track>>();
}

MovementGraph::MovementGraph(int N)
{
    for(int k=0; k<N; ++k) _stations.emplace_back(Station(k));
    _tracks = {};
}

MovementGraph::~MovementGraph()
{
    _stations.clear();
    _tracks.clear();
}

void MovementGraph::addTrack(Track t) {
    // Controllo prima che le stazioni siano nel movement graph (immaginando che Station sia una struttura pià complessa)
    if(std::find(_stations.begin(), _stations.end(), t._stations.first) != _stations.end()
        && std::find(_stations.begin(), _stations.end(), t._stations.second) != _stations.end())
        {
            _tracks.emplace_back(t);
        }
}

void MovementGraph::removeTrack(int track_id)
{
    _tracks.remove_if([track_id](Track t) {return t._id == track_id; });
}

std::vector<Station> MovementGraph::findPivotStations()
{
    std::vector<Station> pivots = {};


    // Ipotizzo che S_0 sia una Pivot Station
    pivots.emplace_back(Station(0));
    return pivots;
}

