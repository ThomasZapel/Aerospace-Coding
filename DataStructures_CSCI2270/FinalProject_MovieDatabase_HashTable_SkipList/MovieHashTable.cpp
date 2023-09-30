#include<iostream>
#include <vector>
#include "MovieHashTable.hpp"
using namespace std;

// Constructor for MovieHashTable with default size
/*
* MovieHashTable - Default Hash Table constructor
* 
*/
MovieHashTable::MovieHashTable() {
    table_size = DEFAULT_HTABLE_CAPACITY;
    n_collisions = 0;
    table = new MovieNode*[table_size];
    
    for(int i = 0; i < table_size; i++) {
        table[i] = nullptr;
    }
    
}

// Constructor for MovieHashTable with given size
/*
* MovieHashTable - Hash Table constructor with user input
* 
*
* @param size
*/
MovieHashTable::MovieHashTable(int s) {
    table_size = s;
    n_collisions = 0;
    table = new MovieNode*[table_size];
    
    for(int i = 0; i < table_size; i++) {
        table[i] = nullptr;
    }
}

// Destructor for MovieHashTable that deletes all nodes in the hash table
/*
* ~MovieHashTable - Hash Table destructor
* - loops through each index in the table and delete the node at that location
* - if that index has a chain it will traverse the chain and delete each node as it traverses
*
*/
MovieHashTable::~MovieHashTable() {
    for(int i = 0; i < table_size; i++) {
        MovieNode *curr = table[i];
        while(curr) {
            MovieNode *temp = curr->next;
            delete curr;
            curr = temp;
        }
        table[i] = nullptr;
    }
    delete[] table;
}

// Hash function for MovieHashTable that returns an index in the hash table for a given movie title.
// Students must use their identikey to come up with a creative hash function that minimizes collisions
// for the given IMDB-Movie database to ensure efficient insertion and retrieval of movie nodes.
/*
* hash - produces a hash key from given title
* - takes each letter in the title and static casts as an int to convert to its ASCII value
* then adds it to the same ASCII value multiplied by the ASCII value of t, then takes the modulo
* of that value and 9253, this is then repated for h, z, and a
* - at the end of this sequence the value is added to a running sum hash
* - once all characters have been manipulated this way the modulo of the running sum
* and the table size is returned
*
* @param title
* @return int
*/
int MovieHashTable::hash(string title) {
    int hash = 0, n;
    for(int i = 0; i < title.length(); i++) {
        n = static_cast<int>(title[i]);
        n = n + ((n * static_cast<int>('t')) % (9253));
        n = n + ((n * static_cast<int>('h')) % (9253));
        n = n + ((n * static_cast<int>('z')) % (9253));
        n = n + ((n * static_cast<int>('a')) % (9253));
        hash = hash + n;
    }
    return (hash % table_size);
}

// Inserts a movie node into the hash table with the specified title
/*
* insert - Inserts a movie node into the hash table
* - calls hash to find the index of the movie node
* - if the bucket is empty it inserts
* - if the bucket is not empty it makes the movie node the new head of a linked list at that bucket
*
* @param title, *movie
* @return void
*/
void MovieHashTable::insert(string title, MovieNode* movie) {
    int index = hash(title);
    if(!table[index]) {
        table[index] = movie;
    } else {
        MovieNode *temp = table[index];
        movie->next = temp;
        table[index] = movie;
    }
}

// Searches for a node in the hash table with the specified title
/*
* search - Searches for a node in the hash table with the specified title
* - uses hash to locate the index of the bucket
* - then taverses the linked list (possibly of length 1) at the bucket until the
* title matches the input title
*
* @param title
* @return MovieNode*
*/
MovieNode* MovieHashTable::search(string title) {
    int index = hash(title);
    MovieNode *temp = table[index];
    while(temp) {
        if(title == temp->title) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Returns the number of collisions that have occurred during insertion into the hash table
/*
* getCollisions - returns collisons in hash table
* 
* @return int
*/
int MovieHashTable::getCollisions() {
    return n_collisions;
}

// Increments the number of collisions that have occurred during insertion into the hash table
/*
* setCollisions - Loops through the Hash Table and counts the number of nodes that are in a linked list
* 
* @return void
*/
void MovieHashTable::setCollisions() {
    int index;
    for(int i = 0; i < table_size; i++) {
        if(table[i]) {
            index = hash(table[i]->title);
            if(table[i]->next) {
                MovieNode *temp = table[i]->next;
                while(temp) {
                    index = hash(temp->title);
                    temp = temp->next;
                    n_collisions++;
                }
            }
        }
    }
}
