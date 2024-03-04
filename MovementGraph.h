// Questa classe rappresenta un Movement Graph:
// Un insieme di Station (nodi del grafo) e Track (archi del grafo che connettono le stazioni)
// Ci possono essere più track che connettono le stesse stazioni

#include <string>
#include <vector>

// Rappresenta un nodo del grafo ("S_i")
struct Station
{
   int _id;

   Station(int id):_id(id){}
};

// Rappresenta un arco del grafo ("T_i")
struct Track
{
    Station *_start;
    Station *_end;

    //TODO: può essere una pair

    int _id;
    
    Track(Station *start, Station *end, int id):_start(start),_end(end),_id(id){}

    std::string to_string() { return "S"+ std::to_string(_start->_id) + " -> <T" + std::to_string(_id) + "> -> S" + std::to_string(_end->_id); };
};


class MovementGraph
{
private:
    std::vector<Station> _stations; // nodi
    std::vector<Track> _tracks; // archi
public:
    MovementGraph(){};
    MovementGraph(std::vector<Station>, std::vector<Track>);

    //TODO: operator >> per aggiungere archi, con controllo esistenza nodi

    ~MovementGraph();
};

MovementGraph::MovementGraph(std::vector<Station> stations, std::vector<Track> tracks):_stations(stations),_tracks(tracks){}

MovementGraph::~MovementGraph()
{
}
