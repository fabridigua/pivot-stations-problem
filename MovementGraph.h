// Questa classe rappresenta un Movement Graph:
// Un insieme di Station (nodi del grafo) e Track (archi del grafo che connettono le stazioni)
// Ci possono essere più track che connettono le stesse stazioni

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility> // Per std::pair

// Rappresenta un nodo del grafo ("S_i")
struct Station
{
   int _id = 0;

   Station(){}
   Station(int id):_id(id){}

   friend bool operator==(const Station& l, const Station& r) { return l._id == r._id; }
};

// Rappresenta un arco del grafo ("T_i")
struct Track
{
    int _id;
    std::pair<Station,Station> _stations;
    
    Track(int start_id, int end_id, int id):_id(id) { _stations = {{start_id}, {end_id}}; }

    std::string to_string() { return "S"+ std::to_string(_stations.first._id) + " -> <T" + std::to_string(_id) + "> -> S" + std::to_string(_stations.second._id); };
};


class MovementGraph
{
private:
    std::vector<Station> _stations; // Nodi del grafo: lista delle stazioni    
    std::list<Track> _tracks; // Archi del grafo: lista delle tracks percorribili

    std::list<std::list<Track>> get_feasable_path();
public:
    MovementGraph(){};    
    MovementGraph(int N); // N = numero di stazioni
    ~MovementGraph();

    void addTrack(Track t);
    void removeTrack(int track_id);

    std::vector<Station> findPivotStations();

    friend std::ostream& operator<<(std::ostream &out, const MovementGraph &m)
    {
        out << "Stations " << m._stations.size() << std::endl;
        for(Track t: m._tracks)  out << t.to_string() << std::endl;
        return out;
    }
};
