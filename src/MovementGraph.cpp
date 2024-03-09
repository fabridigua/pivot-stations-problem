#include "MovementGraph.h"

#include <algorithm> // Per find
#include <set>

MovementGraph::MovementGraph(int N)
{
    for (int k = 0; k < N; ++k) _stations.emplace_back(Station(k));
}

MovementGraph::~MovementGraph()
{
    _stations.clear();
}

std::list<std::list<Track>> MovementGraph::get_feasable_paths(int S_o, int S_d)
{
    if (std::find(_stations.begin(), _stations.end(), S_o) == _stations.end()) return {};
    if (getStation(S_o)._tracks.empty()) return {};

    std::list<std::list<Track>> feasable_paths = {};

    // Lista di appoggio per l'algoritmo di ricerca
    std::list<Track> path = {}; // So che S_o ha almeno un track

    // Chiamo la DFS ricorsivamente
    recursive_dfs(S_o, S_d, path, feasable_paths);

    return feasable_paths;
}

// Algoritmo di Depth First Search: 
void MovementGraph::recursive_dfs(int origin_id, int destination_id, std::list<Track>& curr_path, std::list<std::list<Track>>& paths_found)
{
    //Controllo se le stazioni esistono nel Movement Graph, altrimenti esco
    if (std::find(_stations.begin(), _stations.end(), origin_id) == _stations.end()) return;
    if (std::find(_stations.begin(), _stations.end(), destination_id) == _stations.end()) return;

    // 0. Condizione di uscita: controllo se ho raggiunto la destinazione
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

// Estrae, in ordine, le stazioni presente in un percorso
std::list<int> MovementGraph::get_station_list(const std::list<Track>& path)
{
    if ((path.size() == 0)) return {};
    // Uso un set per sfruttare il fatto che gli elementi sono unici
    std::set<int> stations = {};

    for (auto& t : path)
    {
        stations.insert(t._origin_id);
        stations.insert(t._destination_id);
    }

    return { stations.begin(), stations.end() };
}

void MovementGraph::print_paths(const std::list<std::list<Track>>& feasable_paths, int S_o)
{
    for (auto path_found : feasable_paths)
    {
        std::cout << "S" << S_o;
        for (auto t : path_found)
            std::cout << " -> <T" << t._id << "> -> S" << t._destination_id;
        std::cout << std::endl;
    }
}

// Aggiunge un track alla lista della stazione con id t._origin_id
void MovementGraph::addTrack(Track t) {
    // Controllo prima che le stazioni siano nel movement graph (immaginando che Station sia una struttura pià complessa)
    if (std::find(_stations.begin(), _stations.end(), t._destination_id) == _stations.end()) return;
    auto origin = std::find(_stations.begin(), _stations.end(), t._origin_id);
    if(origin != _stations.end())
        (*origin).addTrack(t);
}

void MovementGraph::addTracks(std::initializer_list<Track> tracks)
{
    for (auto t : tracks) addTrack(t);
}

// Rimuove (se esiste) il track con id track_id nella lista della stazione station_id
void MovementGraph::removeTrack(int station_id, int track_id)
{
    auto station_iter = std::find(_stations.begin(), _stations.end(), station_id);
    if (station_iter == _stations.end()) return;
    (*station_iter)._tracks.erase(std::remove_if(std::begin((*station_iter)._tracks), std::end((*station_iter)._tracks),
        [track_id](Track t) {return t._id == track_id; }), std::end((*station_iter)._tracks));
}

// Rimuove, se esiste, la stazione station_id dal grafo
void MovementGraph::removeStation(int station_id)
{
    auto station = std::find(_stations.begin(), _stations.end(), station_id);
    if (station != _stations.end())
        _stations.erase(station);
}

// Strategia 1
// Cerco le stazioni presenti in tutti i path da S_o a S_d
std::vector<int> MovementGraph::findPivotStations_strategy1(int S_o, int S_d)
{
    std::vector<int> pivots = {};

    // 0. Trovo i percorsi possibili da S_o a S_d
    auto paths_found = get_feasable_paths(S_o, S_d);

    // DEBUG: Stampo la lista di percorsi trovati
    // print_paths(paths_found, S_o);

    // 1. Per ogni stazione del grafo, guardo se è in tutti i path trovati
    for (const auto& s : _stations)
    {
        bool is_pivot = true;
        // 1.1 Cicli i percorsi da S-o a S-d
        for (auto p : paths_found)
        {
            // 1.2 Estraggo le stazioni del percorso
            auto path_stations = get_station_list(p);
            // 1.3 Cerco la stazione: se non c'è so già che non è una pivot station, esco e vado avanti
            if ((std::find(path_stations.begin(), path_stations.end(), s._id) == path_stations.end()))
            {
                is_pivot = false;
                break;
            }
        }
        if (is_pivot) pivots.emplace_back(s._id);
    }

    std::cout << "[Strategy 1] Pivot Stations found between S" << S_o << " and S" << S_d << ":" << std::endl;
    for (auto s : pivots) std::cout << "S" << s << std::endl;

    return pivots;
}

// Strategia 2: elimino una ad una le stazioni tra S_o e S_d: se non ci sono altri percorsi possibili è una pivot
std::vector<int> MovementGraph::findPivotStations_strategy2(int S_o, int S_d)
{
    std::vector<int> pivots = {};

    // Backuppo la lista di stazioni: mi servirà per ripristinare la lista dopo
    auto stations_backup = _stations; 

    // 0. Trovo i percorsi possibili da S_o a S_d
    auto paths_found = get_feasable_paths(S_o, S_d);

    // DEBUG: Stampo la lista di percorsi trovati
    // print_paths(paths_found, S_o);

    if (paths_found.size() == 0) return {};

    // 1. Per ogni stazione del grafo, provo a eliminarla per vedere se trovo ancora perso
    for (const auto& s : _stations)
    {
        int s_id = s._id;
        // 1.1 Rimuovo momentaneamente la stazione dal grafo
        removeStation(s_id);

        // 1.2 Calcolo di nuovo tutti i percorsi possibili da S_o a S_d nel grafo privo della stazione s
        auto paths_found = get_feasable_paths(S_o, S_d);

        // 1.3 Se non ho trovato percorsi dopo aver rimosso la stazione s, è una Pivot Station
        if(paths_found.size() == 0)
            pivots.emplace_back(s_id);

        // 1.4 Ripristino la lista di stazioni
        _stations = stations_backup;
    }
    

    std::cout << std::endl << "[Strategy 2] Pivot Stations found between S" << S_o << " and S" << S_d << ":" << std::endl;
    for (auto s : pivots) std::cout << "S" << s << std::endl;

    return pivots;
}
