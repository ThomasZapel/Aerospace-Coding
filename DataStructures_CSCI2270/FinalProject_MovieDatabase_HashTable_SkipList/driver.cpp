#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "MovieHashTable.hpp"
#include "DirectorSkipList.hpp"

using namespace std;

/*
The Driver file is where the main, parseMovieLine, readMovieCSV, display_menu functions reside.
This the input file is read, parsed, and movie node objects get created before being passed to the insert functions
for the hash table and the skiplist
*/

// Function prototypes
MovieNode* parseMovieLine(string line);
void readMovieCSV(string filename,MovieHashTable &movieTable, DirectorSkipList &directorList);
void display_menu();
vector<MovieNode*> movies;


// Main function
/*
* main - drives the program
* - instantiates the MovieHashTable and DirectorSkipList classes
* - Presents the number of collisions in the hash table
* - presents user with menu and prompts for input
* - executes desired input using MovieHashTable and DirectorSkipList functions
* - frees all memory when the user quits the program
*
* @param argc, argv[]
* @return int
*/
int main(int argc, char* argv[]) {
    // Argument validation
    if(argc != 4) {
        cout << "Invalid number of arguments.\nUsage: ./<program name> <csv file> <hashTable size> <skipList size>" << endl;
        return 0;
    }

    // Declare Variables
    string filename = argv[1];
    int size = stoi(argv[2]);
    int levels = stoi(argv[3]);

    // Input validation
    if(size < 0 && levels < 0) {
        cout << "Invalid Hash Table size and Skip List size, must be greater than 0" << endl;
        return 0;
    } else if(size < 0) {
        cout << "Invalid Hash Table size, must be greater than 0" << endl;
        return 0;
    } else if(levels < 0) {
        cout << "Invalid Skip List size, must be greater than 0" << endl;
        return 0;
    }

    // Instantiate class objects with user input
    MovieHashTable *movieTable = new MovieHashTable(size);
    DirectorSkipList *directorList = new DirectorSkipList(size,levels);

    // Read user input file
    readMovieCSV(filename,*movieTable,*directorList);

    // Set collision variable and display to user
    movieTable->setCollisions();
    cout << "Number of collisions:" << movieTable->getCollisions() << endl; 

    // Begin Switch case for user input 
    int choice = 0;
    bool quit = false;
    while(!quit) {
        display_menu();
        cin >> choice;
        // Input validation
        while(cin.fail()) {
            cin.clear();
            cin.ignore(128,'\n');
            cout << "Invalid input. Please enter an integer: ";
            cin >> choice;
        }
        switch(choice) {
            case 1: {
                // Search for director by movie name
                string title;
                cout << "Enter movie name: ";
                cin.ignore();
                getline(cin,title);
                MovieNode *movie = movieTable->search(title);
                if(movie) {
                    cout << "The director of " << movie->title << " is " << movie->director << endl;
                } else {
                    cout << "Movie not found" << endl;
                }
                break;
            } case 2: {
                // Find the number of movies by a director
                string name;
                cout << "Enter director name: ";
                cin.ignore();
                getline(cin,name);
                DirectorSLNode *director = directorList->search(name);
                if(director) {
                    cout << name << " directed " << director->movies.size() << " movies" << endl;
                } else {
                    cout << "Director not found" << endl;
                }
                break;
            } case 3: {
                // Find the description of a movie by movie name
                string title;
                cout << "Enter movie name: ";
                cin.ignore();
                getline(cin,title);
                MovieNode *movie = movieTable->search(title);
                if(movie) {
                    cout << "Description: " << movie->description << endl;
                    cout << "Actors: " << movie->actors << endl;
                    cout << "Year: " << movie->year << endl;
                    cout << "Genre: " << movie->genre << endl;
                } else {
                    cout << "Movie not found" << endl;
                }
                break;
            } case 4: {
                // List the movies by a director
                string name;
                cout << "Enter director name: ";
                cin.ignore();
                getline(cin,name);
                DirectorSLNode *director = directorList->search(name);
                if(director) {
                    cout << name << " directed the following movies:" << endl;
                    for(int i = 0; i < director->movies.size(); i++) {
                        cout << "\t" << i << ": " << director->movies.at(i)->title << endl;
                    }
                } else {
                    cout << "Director not found" << endl;
                }
                break;
            } case 5: {
                // Quitting
                delete movieTable;
                delete directorList;
                quit = true;
                break;
            }
        }
    }   
    return 0;
}

// Function to parse a CSV line into a MovieNode object
/*
* parseMovieLine - parses given line from csv and parses it to create a movie node
* - parses given line
* - creates a movie line object with new operator
*
* @param line
* @return MovieNode*
*/
MovieNode* parseMovieLine(string line) {
    stringstream ss(line);
    vector<string> fields;
    string field;

    // Loop through the characters in the line
    bool in_quotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '\"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            // add field to vector and reset for next field
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
            // handle double quotes inside a quoted field
            if (in_quotes && c == '\"' && i < line.length() - 1 && line[i+1] == '\"') {
                field += '\"'; // add the second double quote and skip it
                ++i;
            }
        }
    }
    fields.push_back(field);

    if (fields.size() != 12) {
        cerr << "Error: Invalid movie line format" << line << endl;
        return nullptr;
    }

    int rank = stoi(fields[0]);
    string title = fields[1];
    string genre = fields[2];
    string description = fields[3];
    string director = fields[4];
    string actors = fields[5];
    int year = stoi(fields[6]);
    int runtime = stoi(fields[7]);
    float rating = stof(fields[8]);
    int votes = stoi(fields[9]);
    float revenue = stof(fields[10]);
    int metascore = stoi(fields[11]);

    // Create a new MovieNode object with the parsed fields
    MovieNode* movie = new MovieNode(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);
    return movie;
}

// Function to read a CSV file into a vector of MovieNode objects
/*
* readMovieCSV - reads the user input file and inserts movie objects into Hash Table and Skip List
* - reads user input file line by line
* - passes each line to parseMovieLine
* - inserts the returned movie node into the Hash Table and Skip List
*
* @param filename, &movieTable, &directorList
* @return void
*/
void readMovieCSV(string filename,MovieHashTable &movieTable, DirectorSkipList &directorList) {
    // Open ifstream object
    string line;
    ifstream inFile;
    inFile.open(filename.c_str());

    // Read first line to discard file header
    getline(inFile,line);

    // Loop through file and pass node to insert functions
    MovieNode *newNode;
    while(getline(inFile,line)) {
        newNode = parseMovieLine(line);
        movieTable.insert(newNode->title,newNode);
        directorList.insert(newNode->director,newNode);
    }
    
    inFile.close();
}

// Function to display the menu options
/*
* display_menu - displays the menu options to the user
* 
* @param 
* @return void
*/
void display_menu() {
    // TODO
    cout << "Please select an option:" << endl;
    cout << "1. Find the director of a movie" << endl;
    cout << "2. Find the number of movies by a director" << endl;
    cout << "3. Find the description of a movie" << endl;
    cout << "4. List the movies by a director" << endl;
    cout << "5. Quit" << endl;
    cout << "Enter an Option: ";

}
