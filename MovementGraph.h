// Questa classe rappresenta un Movement Graph:
// Un insieme di Station (nodi del grafo) e Track (archi del grafo che connettono le stazioni)
// Ci possono essere più track che connettono le stesse stazioni

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility> // Per std::pair

// Rappresenta un arco del grafo ("T_i")
struct Track
{
    int _id;
    int _origin_id;
    int _destination_id;

    Track(int origin_id, int destination_id, int track_id) :_id(track_id), _origin_id(origin_id), _destination_id(destination_id) {}
};

// Rappresenta un nodo del grafo ("S_i")
struct Station
{
   int _id = 0;

   std::vector<Track> _tracks;

   Station(){}
   Station(int id) :_id(id) { _tracks = {}; }

   void addTrack(Track t) { _tracks.emplace_back(t); }

   friend bool operator==(const Station& l, const Station& r) { return l._id == r._id; }

   std::string to_string() { 
       std::string tracks_str = "";
       for(auto t: _tracks)
           tracks_str += "S" + std::to_string(_id) + " -> <T" + std::to_string(t._id) + "> -> S" + std::to_string(t._destination_id) + "\n";
       return tracks_str;
   };
};


class MovementGraph
{
private:
    std::vector<Station> _stations; // Nodi del grafo: lista delle stazioni    

    std::list<std::list<Track>> get_feasable_paths(int S_o, int S_d);

    void recursive_dfs(int origin_id, int destination_id, std::list<Track>& curr_path, std::list<std::list<Track>>& paths_found);

    // Metodo di utility: estrae la lista di stazioni (id) da un path (ovvero una lista di track)
    std::list<int> get_station_list(std::list<Track> path);
    
public:
    MovementGraph(){};    
    MovementGraph(int N); // N = numero di stazioni
    ~MovementGraph();

    void addTrack(Track t);
    void removeTrack(int station_id, int track_id);

    void removeStation(int station_id);

    std::vector<int> findPivotStations_strategy1(int S_o, int S_d);
    std::vector<int> findPivotStations_strategy2(int S_o, int S_d);
    std::vector<int> findPivotStations_strategy3(int S_o, int S_d);

    friend std::ostream& operator<<(std::ostream &out, const MovementGraph &m)
    {
        out << "Stations " << m._stations.size() << std::endl;
        for(Station s: m._stations) 
            if(s._tracks.size() > 0) out << s.to_string();
        return out;
    }

    // Per semplicità ho assegnato alle stazioni un id incrementale (nel costruttore)
    // Tuttavia potrebbero avere un id casuale, quindi voglio poterci accedere con con l'id in modo sicuro
    Station& getStation(int station_id) {
        auto station_iter = std::find(_stations.begin(), _stations.end(), station_id);
        return *station_iter;
    }
};
