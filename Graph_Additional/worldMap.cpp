#include "worldMap.hpp"
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

WorldMap::WorldMap() {}

void WorldMap::createWorldMap(string fileName) {
    string line;
    stringstream stream;
    ifstream inFile;
    inFile.open(fileName.c_str());
    getline(inFile,line);
    stream << line;
    rows = stoi(line.substr(0,line.find(' ')));
    cols = stoi(line.substr(1,line.find('\n')));

    
    worldMap = new int*[rows];
    for(int i = 0; i < rows; i++) {
        worldMap[i] = new int[cols];
    }
    int i = 0;
    int temp;
    while(getline(inFile, line)) {  
        stream << line;
        for(int j = 0; j < cols; j++) {
            temp = stoi(line.substr(0, line.find(' ')));
            line.erase(0, line.find(' ') + 1);
            worldMap[i][j] = temp;
        }        
        i++;
    }
    

}

void WorldMap::printWorldMap() {
    
    for(int i = 0; i < rows; i++) {
        cout << "|";
        for(int j = 0; j < cols; j++) {
            cout << " " << worldMap[i][j] << " |";
        }
        cout << "\n";
    }

}

void WorldMap::addRegion(int x, int y) {
    for(auto p : regions) {
        if(p->x == x && p->y == y) {
            return;
        }
    }
    Region *r = new Region;
    r->x = x;
    r->y = y;
    regions.push_back(r);

}

bool checkIfEdgeExists(Region *r, int x2, int y2) {
    if(r->neighbors.size() == 0) {
        return false;
    }
    int i = 0;
    for(int i = 0; i < r->neighbors.size(); i++) {
        if(x2 == r->neighbors.at(i).region->x && y2 == r->neighbors.at(i).region->y) {
            return true;
        }
    }
}

void WorldMap::addEdgeBetweenRegions(int x1, int y1, int x2, int y2) {
    for(unsigned int i = 0; i < regions.size(); i++){
        if(regions[i]->x == x1 && regions[i]->y == y1){
            for(unsigned int j = 0; j < regions.size(); j++){
                if(i != j && regions[j]->x == x2 && regions[j]->y == y2){
                    if(!checkIfEdgeExists(regions[i], x2, y2)){
                        NeighboringRegion av;
                        av.region = regions[j];
                        regions[i]->neighbors.push_back(av);
                        // another vertex for edge in other direction
                        NeighboringRegion av2;
                        av2.region = regions[i];
                        regions[j]->neighbors.push_back(av2);
                    }
                }
            }
        }
    }
}

vector<vector<int>> WorldMap::findAdjacentLandRegions(int x, int y) {
    // identify the open paths that are adjacent to the vertex at x, y
    // fill adjArr array with the numbers of the adjacent vertices
    vector<vector<int>> neighbors; 
    for(int i = x-1; i <= x + 1; i++){
        if(i < 0 || i >= this->rows){
            continue;
        }
        for(int j = y-1; j <= y+1; j++){
            if(j < 0 || j >= this->cols){
                continue;
            }
            // if there is an open path at this adjacent position, add to adjArray
            if(!(i == x && j == y) && worldMap[i][j] == 1){
                neighbors.push_back({i,j});
            }
        }
    }
    return neighbors;
}

void WorldMap::convertWorldMapToAdjacencyListGraph() {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(worldMap[i][j] == 1) {
                WorldMap::addRegion(i,j);
            }
        }
    }
    int i = 0;
    for(auto r : regions) {
        vector<vector<int>> neighbors = WorldMap::findAdjacentLandRegions(r->x,r->y);
        if(neighbors.size() > 0) {
            for (int i = 0; i < neighbors.size(); i++) {
                for (int j = 0; j < neighbors[i].size()-1; j++) {
                    WorldMap::addEdgeBetweenRegions(r->x,r->y,neighbors[i][j],neighbors[i][j+1]);
                }
            }
        }
        i++;
    }

}

// helper function to check if v2 is a neighbor of vertex v1
bool isNeighbor(int x1, int y1, int x2, int y2, const vector<Region *> regions) {
    return false;
}

WorldMap::~WorldMap(){
}

void WorldMap::displayEdges() {
    int i = 0;
    for(auto r : regions) {
        cout <<"("<< r->x <<","<< r->y <<") --> ";
        for(auto v : r->neighbors) {
            cout <<"("<< v.region->x <<","<< v.region->y <<") ";
        }
        cout << "\n";

        i++;
    }
}

// HELPER FOR findNumOfIslands
void findNumOfIslandsHelper(Region *r) {
    r->visited = true;
    for(int i = 0; i < r->neighbors.size(); i++) {
        Region *v = r->neighbors.at(i).region;
        if(!v->visited) {
            findNumOfIslandsHelper(v);
        }
    }
    return;
}

int WorldMap::findNumOfIslands() {
    int islands = 0;
    for(auto r : regions) {
        if(!r->visited) {
            findNumOfIslandsHelper(r);
            islands++;
        }
    }
    
    return islands;
}

vector<Region *> &WorldMap::getRegions() {
    return regions;
}
