#include <iostream>

#include "MovementGraph.h"

int main() {

    // Creo il grafo dell'esempio (vedi "movement_graph_esempio_1.png")
    int num_stations = 7;

    MovementGraph m(num_stations);
    m.addTrack({0, 1, 0});
    m.addTrack({0, 2, 1});
    m.addTrack({0, 4, 2});
    m.addTrack({2, 1, 3});
    m.addTrack({2, 3, 4});
    m.addTrack({2, 3, 5});
    m.addTrack({4, 3, 6});
    m.addTrack({1, 3, 7});
    m.addTrack({1, 5, 8});
    m.addTrack({3, 5, 9});
    m.addTrack({3, 5, 10});
    m.addTrack({5, 6, 11});    
    m.addTrack({1, 6, 12});

    std::cout << "Movement Graph - Esempio 1" << std::endl << m << std::endl;

    // Strategia 1: cerco le stazioni presenti in tutti i path da S_o a S_d
    std::vector<int> pivots_s1 = m.findPivotStations_strategy1(0, 6); // Returns [S_0, S_6]

    // Strategia 2: elimino una ad una le stazioni tra S_o e S_d: se non ci sono altri percorsi possibili è una pivot
    std::vector<int> pivots_s2 = m.findPivotStations_strategy2(0, 6); // Returns [S_0, S_6]

    // Nel Movement Graph di esempio non sono presenti pivot points, ad esclusione degli stessi S_o e S_d
    // Tuttavia se ad esempio elimino T12 (vedi "movement_graph_esempio_1_noT12.png"), ecco che S_5 diventa una pivot station:
    m.removeTrack(1, 12);
    pivots_s1 = m.findPivotStations_strategy1(0, 6); // Returns [S_0, S_5, S_6]
    pivots_s2 = m.findPivotStations_strategy2(0, 6); // Returns [S_0, S_5, S_6]

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Per test costruisco un Movement Graph più complesso, 
    // in cui sono presenti più pivots station ("movement_graph_esempio_2.png")
    // Mi aspetto come pivot stations: S_0, S_1, S_6, S_7, S_10
    num_stations = 11;

    MovementGraph m2(num_stations);
    m2.addTrack({ 0, 1, 0 });
    m2.addTrack({ 1, 2, 1 });
    m2.addTrack({ 1, 3, 2 });
    m2.addTrack({ 2, 4, 3 });
    m2.addTrack({ 4, 5, 4 });
    m2.addTrack({ 5, 6, 5 });
    m2.addTrack({ 3, 6, 6 });
    m2.addTrack({ 6, 7, 7 });
    m2.addTrack({ 7, 8, 8 });
    m2.addTrack({ 7, 9, 9 });
    m2.addTrack({ 8, 10, 10 });
    m2.addTrack({ 9, 10, 11 });

    std::cout << "Movement Graph - Esempio 2" << std::endl << m2 << std::endl;

    pivots_s1 = m2.findPivotStations_strategy1(0, 10); // Returns [S_0, S_1, S_6, S_7, S_10]
    pivots_s2 = m2.findPivotStations_strategy2(0, 10); // Returns [S_0, S_1, S_6, S_7, S_10]

    return 0;
}