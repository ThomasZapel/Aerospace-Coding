#pragma once
#ifndef BookCollection_H__
#define BookCollection_H__

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>

#include <vector>

// Base class
#include "../library/BookCollectionBase.hpp"

using namespace std; 

class BookCollection : public BookCollectionBase {

    public:
        BookCollection();
        ~BookCollection();

        void removeBook(string bookName);
        void rotateLeftCollection(string bookName); // (LEFT ROTATE – To be mentioned in the readme) 
        string closestParent(string book1, string book2); // (Lowest Common Ancestor in a BST)
        void rotateHelp(Book *,Book *, string);
        Book* getRoot(){
            return root;
        }

        void _DestructorHelper(Book *);
        void removeHelper(Book *&, string);
        Book* minHelper(Book *);
        void closestHelper(Book *, string, vector<string>&);

        vector<string> family1;
        vector<string> family2;
};

#endif
