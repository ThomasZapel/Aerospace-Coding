#include "LinkedInNetwork.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void LinkedInNetwork::addProfessional(string name) {
    bool found = false;
    for(int i = 0; i < professionals.size(); i++) {
        if(professionals[i]->name == name) {
            found = true;
            cout << name << " found." << endl;
        }
    }
    if(!(found)) {
        Professional *vertex = new Professional;
        vertex->name = name;
        professionals.push_back(vertex);
    }
}

void LinkedInNetwork::addConnection(string v1, string v2) {
    for(int i = 0; i < professionals.size(); i++) {
        if(professionals.at(i)->name == v1) {
            Professional *pointer_v1 = professionals.at(i);
            neighbor A;
            A.v = pointer_v1;
            for(int j = 0; j < professionals.size(); j++) {
                if(professionals.at(j)->name == v2) {
                    professionals.at(j)->neighbors.push_back(A);
                }
            }
        } else if(professionals.at(i)->name == v2) {
            Professional *pointer_v2 = professionals.at(i);
            neighbor B;
            B.v = pointer_v2;
            for(int j = 0; j < professionals.size(); j++) {
                if(professionals.at(j)->name == v1) {
                    professionals.at(j)->neighbors.push_back(B);
                }
            }
        }
    }
}

void LinkedInNetwork::displayConnections() {
    for(int i = 0; i < professionals.size(); i++) {
        // loop through each vertex and display its own name and its neighbor(s)
        cout << professionals.at(i)->name << " --> ";
        for(int j = 0; j < professionals.at(i)->neighbors.size(); j++) {
            cout << professionals.at(i)->neighbors.at(j).v->name << " ";
        }
        cout << "\n";
    }
}

void LinkedInNetwork::breadthFirstTraverse(string sourceProfessional) {
    // for the source vertex in the network
    cout << "Starting Professional (root): " << sourceProfessional << "-> ";
    
    queue<Professional*> queue;
    Professional *start = nullptr;
    for(auto p : professionals) {
        if(p->name == sourceProfessional) {
            start = p;
        }
    }
    start->visited = true;
    queue.push(start);

    Professional *curr = nullptr;
    int i = 0;
    while(!queue.empty()) {
        curr = queue.front();
        queue.pop();
        if(!(i == 0)) {
            cout << curr->name << "(" << curr->connectionOrder << ") ";
        } else {}
        

        for(auto p : curr->neighbors) {
            if(!p.v->visited) {
                p.v->visited = true;
                queue.push(p.v);
                p.v->connectionOrder = curr->connectionOrder + 1;
            }
        }
        i++;
    }        
}


void bfs_helper(string source, vector<Professional*> &professionals) {
    queue<Professional*> queue;
    Professional *start = nullptr;
    for(auto p : professionals) {
        if(p->name == source) {
            start = p;
        }
    }
    if(start == nullptr) {
        return;
    }
    start->visited = true;
    queue.push(start);
    
    Professional *curr = nullptr;
    int i = 0;
    while(!queue.empty()) {
        curr = queue.front();
        queue.pop();
        
        for(auto p : curr->neighbors) {
            if(!p.v->visited) {
                p.v->visited = true;
                queue.push(p.v);
                p.v->connectionOrder = curr->connectionOrder + 1;
            }
        }
    }
    

}


vector<string> LinkedInNetwork::suggestProfessionalsWithinKthOrder(string professionalName, int k){

    vector<string> professionalsWithinK;
    bfs_helper(professionalName,professionals);

    for(auto p : professionals) {
        if(p->connectionOrder < k+1 && p->visited && !(p->name == professionalName)) {
            professionalsWithinK.push_back(p->name);
        }
    }

    // Post Processing
    if(professionalsWithinK.size() == 0) {
        return professionalsWithinK;
    }

    return professionalsWithinK;
}