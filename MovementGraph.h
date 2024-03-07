// Questa classe rappresenta un Movement Graph:
// Un insieme di Station (nodi del grafo) e Track (archi del grafo che connettono le stazioni)
// Ci possono essere più track che connettono le stesse stazioni

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <initializer_list>

// Rappresenta un arco del grafo ("T_i")
struct Track
{
    int _id; // Id del track
    int _origin_id; // Id della stazione di partenza
    int _destination_id; // Id della stazione di arrivo

    Track(int origin_id, int destination_id, int track_id) :_id(track_id), _origin_id(origin_id), _destination_id(destination_id) {}
};

// Rappresenta un nodo del grafo ("S_i")
struct Station
{
   int _id = -1;
   std::vector<Track> _tracks;

   Station(){}
   Station(int id) :_id(id) { _tracks = {}; }

   void addTrack(Track t) { _tracks.emplace_back(t); }

   friend bool operator==(const Station& l, const Station& r) { return l._id == r._id; } // Serve per poter usare std::find

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
    // Nodi del grafo: lista delle stazioni    
    std::vector<Station> _stations; 

    // Ricerca tutti i percorsi possibili tra S_o e S_d, descritti come liste di Track
    std::list<std::list<Track>> get_feasable_paths(int S_o, int S_d);
    // Depth First Search: visita in modo ricorsivo le stazioni del grafo per trovare i percorsi possibili
    void recursive_dfs(int origin_id, int destination_id, std::list<Track>& curr_path, std::list<std::list<Track>>& paths_found);

    // Metodo di utility: estrae la lista di stazioni (id) da un path (ovvero una lista di track)
    std::list<int> get_station_list(const std::list<Track>& path);
    void print_paths(const std::list<std::list<Track>>& paths, int S_o);
    
public:
    MovementGraph(){};    
    MovementGraph(int N); // N = numero di stazioni
    ~MovementGraph();

    // Aggiunge un track nella lista della stazione di origine
    void addTrack(Track t);
    void addTracks(std::initializer_list<Track> tracks);
    // Rimuove un track dalla lista della stazione con id station_id
    void removeTrack(int station_id, int track_id);
    // Rimuove una stazione dal grafo
    void removeStation(int station_id);

    // Strategia 1: cerco le stazioni presenti in tutti i path da S_o a S_d
    std::vector<int> findPivotStations_strategy1(int S_o, int S_d);
    // Strategia 2: elimino una ad una le stazioni tra S_o e S_d: se non ci sono altri percorsi possibili è una pivot
    std::vector<int> findPivotStations_strategy2(int S_o, int S_d);

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
