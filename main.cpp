#include <iostream>

#include "MovementGraph.h"

int main() {

    // Creo il grafo dell'esempio
    int num_stations = 7;
    MovementGraph m(num_stations);
    m.addTrack({0,1, 0});
    m.addTrack({0,2, 1});
    m.addTrack({0,4, 2});
    m.addTrack({2,1, 3});
    m.addTrack({2,3, 4});
    m.addTrack({2,3, 5});
    m.addTrack({4,3, 6});
    m.addTrack({1,3, 7});
    m.addTrack({1,5, 8});
    m.addTrack({3,5, 9});
    m.addTrack({3,5, 10});
    m.addTrack({5,6, 11});    
    m.addTrack({1,6, 12}); //Nota: nel grafo di esempio sono presenti due "T10", chiamo "T12" quello tra S_1 e S_6

    std::cout << "Test Movement Graph" << std::endl << m << std::endl;

    // Strategia 1: cerco le stazioni presenti in tutti i path da S_o a S_d
    //std::vector<int> pivots = m.findPivotStations_strategy1(0, 6);

    // Strategia 2: elimino una ad una le stazioni tra S_o e S_d: se non ci sono altri percorsi possibili è una pivot
    std::vector<int> pivots_s2 = m.findPivotStations_strategy2(0, 6);

    // Idea 3: trovo tutti i possibili percorsi, itero le stazioni e vedo quali
    //         il predecessore non ha alternative che quella
    //          TODO: l'idea 3 è troppo astrusa


    return 0;
}