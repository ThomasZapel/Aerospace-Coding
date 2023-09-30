#include <iostream>
#include <vector>
#include "../code/worldMap.hpp"
#include <string>
using namespace std;

int main(int argc, char** argv) {
    WorldMap* wmap = new WorldMap; 

    wmap->createWorldMap(argv[1]);
    // wmap->addRegion(0, 0);
    // wmap->addRegion(0, 2);
    // wmap->addRegion(1, 3);
    // wmap->addRegion(1, 3);
    // wmap->addRegion(2, 0);
    // wmap->addRegion(2, 1);
    // wmap->addRegion(2, 2);
    // wmap->addRegion(2, 4);
    // wmap->addRegion(3, 3);
    // wmap->addRegion(4, 0);
    // wmap->addRegion(4, 1);
    // wmap->addRegion(4, 3);

    // wmap->addEdgeBetweenRegions(0, 2, 1, 3);
    // wmap->addEdgeBetweenRegions(1, 3, 1, 4);


    //wmap->createWorldMap(argv[1]);
    wmap->printWorldMap();
    wmap->convertWorldMapToAdjacencyListGraph();
    wmap->findNumOfIslands();
    wmap->~WorldMap();

    // wmap->convertWorldMapToAdjacencyListGraph();
    // wmap->displayEdges();
    // cout << "\n" << endl;
    // cout << wmap->findNumOfIslands() << endl;


    return 0;
}