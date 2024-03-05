// Questa classe rappresenta un Movement Graph:
// Un insieme di Station (nodi del grafo) e Track (archi del grafo che connettono le stazioni)
// Ci possono essere più track che connettono le stesse stazioni

#include <string>
#include <vector>
#include <list>
#include <utility> // Per std::pair
#include <set>
#include <algorithm> // Per find

// Rappresenta un nodo del grafo ("S_i")
struct Station
{
   int _id;

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
public:
    MovementGraph(){};
    // N = numero di stazioni
    MovementGraph(int N)
    {
        for(int k=0; k<N; ++k) _stations.emplace_back(Station(k));
        _tracks = {};
    }

    void addTrack(Track t) {
        // Controllo prima che le stazioni siano nel movement graph (immaginando che Station sia una struttura pià complessa)
        if(std::find(_stations.begin(), _stations.end(), t._stations.first) != _stations.end()
            && std::find(_stations.begin(), _stations.end(), t._stations.second) != _stations.end())
            {
                _tracks.emplace_back(t);
            }
    }

    friend std::ostream& operator<< (std::ostream &out, const MovementGraph &m)
    {
        out << "Stations " << m._stations.size() << std::endl;
        for(Track t: m._tracks) 
            out << t.to_string() << std::endl;
        return out;
    }

    ~MovementGraph();
};

// std::ostream& operator << (std::ostream &out, const MovementGraph &m)
// {
//     out << "Stations " << m._stations.size() << std::endl;
//     for(Track t: m._tracks) 
//         out << t.to_string() << std::endl;
//     return out;
// }


MovementGraph::~MovementGraph()
{
}
