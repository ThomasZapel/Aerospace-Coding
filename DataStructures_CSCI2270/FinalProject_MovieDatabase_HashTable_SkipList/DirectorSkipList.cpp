#include<iostream>
#include <vector>
#include "DirectorSkipList.hpp"
using namespace std;

// Constructor for DirectorSkipList with default capacity and levels
/*
* DirectorSkipList - Default Skip List constructor
* 
*/
DirectorSkipList::DirectorSkipList() {
    capacity = DEFAULT_CAPACITY;
    levels = DEFAULT_LEVELS;
    head = nullptr;
    size = 0;
}

// Constructor for DirectorSkipList with given capacity and levels
/*
* DirectorSkipList - Skip List constructor with user input
* 
* @param _cap, _levels
*/
DirectorSkipList::DirectorSkipList(int _cap, int _levels) {
    capacity = _cap;
    levels = _levels;
    head = nullptr;
    size = 0;
}

// Destructor for DirectorSkipList that deletes all nodes in the skip list (but not the MovieNodes, which are shared with other data structures)
/*
* ~DirectorSkipList - Skip List destructor
*  - similar to a lnked list destructor, this will traverse the lowest level of the skip list
* and delete nodes as it traverses
*
*/
DirectorSkipList::~DirectorSkipList() {
    DirectorSLNode *curr = head;
    while(curr) {
        DirectorSLNode *temp = curr;
        curr = curr->next[0];
        delete temp;
    }
    size = 0;
}

// Inserts a movie node into the skip list with the specified director
/*
* insert - Inserts a movie node into the skip list with the specified director
* - searches where the node shoudl be insrted and keeps track of traversed pointers in a previous vector
* - using the vector it then sets the new Node's next pointers to the previous vectors next pointers
* - then sets the previous vectors next pointers to the new Node
*
* @param director, _movie
*/
void DirectorSkipList::insert(string director, MovieNode* _movie) {
    if(search(director)) {
        // Node in skip list already exists with this director
        // Add the movie node to its movie node vector
        DirectorSLNode *existingNode = search(director);
        existingNode->addMovie(_movie);
        return;
    }

    // Edge case for empty list
    if(!head) {
        head = new DirectorSLNode("head",levels);
    }
    
    // Adding Levels
    int nodeLevels = 1;
    while(nodeLevels < levels && rand() % 2 == 0) {
        nodeLevels++;
    }

    // Creating a New Node
    DirectorSLNode *newNode = new DirectorSLNode(director,nodeLevels);
    newNode->addMovie(_movie);

    vector<DirectorSLNode*> prev(levels,nullptr);
    DirectorSLNode *curr = head;
    
    // For loop to descend levels
    for(int i = levels - 1; i >= 0; i--) {
        // While loop to skip levels
        while(curr->next.at(i) && curr->next.at(i)->director < director) {
            curr = curr->next.at(i);
        }
        // Record previous pointers
        prev.at(i) = curr;
    }

    // loop through each level and adjust previous node next pointers and newNode next pointers
    for(int i = 0; i < nodeLevels; i++) {
        newNode->next.at(i) = prev.at(i)->next.at(i);
        prev.at(i)->next.at(i) = newNode;
    }
    // Increment size of the skip list
    size++;
}

// Searches for a node in the skip list with the specified director
/*
* search - searches the skip list with specified director
* - starting at the highest level decends down levels until a node that is less than director is hit
* - then the search will then skip until the next pointer is null and the director equal to or greater than
* - once the search stops the pointer is brought to the lowest level and if the pointer is not null
* and matches the given director name the pointer is returned
*
* @param director
* @return DirectorSLNode*
*/
DirectorSLNode *DirectorSkipList::search(string director) {
    DirectorSLNode *curr = head;
    if(!curr) {
        return nullptr;
    }

    // For loop to descend levels
    for(int i = levels - 1; i >= 0; i--) {
        // While loop to skip levels
        while(curr->next.at(i) && curr->next.at(i)->director < director) {
            curr = curr->next.at(i);
        }
    }
    
    curr = curr->next.at(0);
    if(curr && curr->director == director) {
        return curr;
    }

    return nullptr;
}

// Pretty-prints the skip list
/*
* prettyPrint - Traverses the lowest level of the skip list and prints the nodes as it traverses
* 
*/
void DirectorSkipList::prettyPrint() {
    DirectorSLNode *curr = head;
    if(!curr) {
        cout << "list empty";
    }
    cout << curr->director;
    curr = curr->next.at(0);
    while(curr) {
        cout << " -> " << curr->director;
        curr = curr->next.at(0);
    }
    cout << endl;
}
