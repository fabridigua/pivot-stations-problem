#include "MovementGraph.h"

#include <algorithm> // Per find
#include <set>

std::list<std::list<Track>> MovementGraph::get_feasable_paths(int S_o, int S_d)
{
    if (std::find(_stations.begin(), _stations.end(), S_o) == _stations.end()) return {};
    if (getStation(S_o)._tracks.empty()) return {};

    std::list<std::list<Track>> feasable_paths = {};

    std::list<Track> path = {  }; // So che S_o ha almeno un track

    // Chiamo la DFS
    recursive_dfs(S_o, S_d, path, feasable_paths);

    // Stampo la lista di percorsi trovati
    for (auto path_found : feasable_paths)
    {
        std::cout << "S" << S_o;
        for (auto t : path_found)
        {
            std::cout << " -> <T" << t._id << "> -> S" << t._destination_id;
        }
        std::cout << std::endl;
    }

    return feasable_paths;
}

void MovementGraph::recursive_dfs(int origin_id, int destination_id, std::list<Track>& curr_path, std::list<std::list<Track>>& paths_found)
{
    //Controllo se le stazioni esistono nel Movement Graph, altrimenti esco
    if (std::find(_stations.begin(), _stations.end(), origin_id) == _stations.end()) return;
    if (std::find(_stations.begin(), _stations.end(), destination_id) == _stations.end()) return;

    // 0. Controllo se ho raggiunto la destinazione
    if (origin_id == destination_id)
    {
        paths_found.emplace_back(curr_path);
        return;
    }

    // 1. Ciclo tutti i track della stazione origin_id
    auto S = getStation(origin_id);
    for (Track& t : S._tracks)
    {
        // 1.1 Aggiungo il percorso S -> <t.id> -> t.destination al path corrente
        curr_path.push_back(t);
        // 1.2 Chiamo nuovamente la dfs sulla stazione di arrivo
        recursive_dfs(t._destination_id, destination_id, curr_path, paths_found);
        // 1.3 Se non ho trovato un percorso verso destination_id tolgo t e vado avanti
        curr_path.pop_back();
    }
}

std::list<int> MovementGraph::get_station_list(std::list<Track> path)
{
    std::set<int> stations = {};

    if (path.size() > 0)
    {
        for (auto& t : path)
        {
            stations.insert(t._origin_id);
            stations.insert(t._destination_id);
        }
    }

    return { stations.begin(), stations.end() };
}



MovementGraph::MovementGraph(int N)
{
    for(int k=0; k<N; ++k) _stations.emplace_back(Station(k));
}

MovementGraph::~MovementGraph()
{
    _stations.clear();
}

void MovementGraph::addTrack(Track t) {
    // Controllo prima che le stazioni siano nel movement graph (immaginando che Station sia una struttura pià complessa)
    auto origin = std::find(_stations.begin(), _stations.end(), t._origin_id);
    if(origin != _stations.end()
        && std::find(_stations.begin(), _stations.end(), t._destination_id) != _stations.end())
    {
        (*origin).addTrack(t);
    }
}

void MovementGraph::removeTrack(int station_id, int track_id)
{
    if (std::find(_stations.begin(), _stations.end(), station_id) == _stations.end()) return;
    auto station = getStation(station_id);
    station._tracks.erase(std::remove_if(std::begin(station._tracks), std::end(station._tracks), 
        [track_id](Track t) {return t._id == track_id; }), std::end(station._tracks));
}

void MovementGraph::removeStation(int station_id)
{
    auto station = std::find(_stations.begin(), _stations.end(), station_id);
    if (station != _stations.end())
        _stations.erase(station);
}

// Strategia 1: cerco le stazioni presenti in tutti i path da S_o a S_d
std::vector<int> MovementGraph::findPivotStations_strategy1(int S_o, int S_d)
{
    std::vector<int> pivots = {};

    auto paths_found = get_feasable_paths(S_o, S_d);

    for (const auto& s : _stations)
    {
        bool is_pivot = true;
        for (auto p : paths_found)
        {
            auto path_stations = get_station_list(p);
            if (!(std::find(path_stations.begin(), path_stations.end(), s._id) != path_stations.end()))
            {
                is_pivot = false;
                break;
            }
        }
        if (is_pivot) pivots.emplace_back(s._id);
    }

    std::cout << "[Strategy 1] Pivot Stations found between S" << S_o << " and S" << S_d << ":" << std::endl;
    for (auto s : pivots)
        std::cout << "S" << s << std::endl;

    return pivots;
}

// Strategia 2: elimino una ad una le stazioni tra S_o e S_d: se non ci sono altri percorsi possibili è una pivot
std::vector<int> MovementGraph::findPivotStations_strategy2(int S_o, int S_d)
{
    std::vector<int> pivots = {};

    auto stations_backup = _stations;

    auto paths_found = get_feasable_paths(S_o, S_d);

    if (paths_found.size() == 0) return {};

    for (const auto& s : _stations)
    {
        int s_id = s._id;
        removeStation(s_id);

        auto paths_found = get_feasable_paths(S_o, S_d);

        // Se non ho trovato percorsi dopo aver rimosso la stazione s, è una Pivot Station
        if(paths_found.size() == 0)
            pivots.emplace_back(s_id);

        _stations = stations_backup;
    }
    

    std::cout << std::endl << "[Strategy 2] Pivot Stations found between S" << S_o << " and S" << S_d << ":" << std::endl;
    for (auto s : pivots)
        std::cout << "S" << s << std::endl;

    return pivots;
}

// Strategia 3: TODO
std::vector<int> MovementGraph::findPivotStations_strategy3(int S_o, int S_d)
{
    return std::vector<int>();
}

