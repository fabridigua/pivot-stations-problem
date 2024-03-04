#include <iostream>

#include "MovementGraph.h"

int main() {

    std::vector<Station> stations = {
        {0}, {1}, {2}, {3}, {4}, {5}, {6}
    };

    std::vector<Track> tracks = {
        {&stations[0], &stations[1], 0}, 
        {&stations[0], &stations[2], 1},
        {&stations[0], &stations[4], 2}
        //...
    };

    MovementGraph m(stations, tracks);

    std::cout << "test" << std::endl;

    for(auto e: tracks) std::cout << e.to_string() << std::endl;

    return 0;
}