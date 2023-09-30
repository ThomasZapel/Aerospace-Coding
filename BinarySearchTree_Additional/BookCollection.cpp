#include "BookCollection.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

BookCollection::BookCollection() {
    root = nullptr;
}

BookCollection::~BookCollection() {
    if(root == 0) {
        return;
    } else if((root->left == 0) & (root->right == 0)) {
        delete root;
        root = nullptr;
        return;
    } else {
        BookCollection::_DestructorHelper(root);
    }
}

void BookCollection::_DestructorHelper(Book *T) {
    if(T->left == 0 & T->right == 0) {
        delete T;
        return;
    } else if(T->left == 0) {
        BookCollection::_DestructorHelper(T->right);
        delete T;
        return;
    } else if(T->right == 0) {
        BookCollection::_DestructorHelper(T->left);
        delete T;
        return;
    } else {
        BookCollection::_DestructorHelper(T->left);
        BookCollection::_DestructorHelper(T->right);
        delete T;
        return;
    }
}

void BookCollection::removeBook(string bookName) {
    BookCollection::removeHelper(root, bookName);
}

void BookCollection::removeHelper(Book *&curr, string bookName) {
    if(!(curr)) {
        cout << "Book not found!" << endl;
        return;
    } else if(bookName < curr->bookName) {
        BookCollection::removeHelper(curr->left,bookName);
    } else if(bookName > curr->bookName) {
        BookCollection::removeHelper(curr->right,bookName);
    } else { // bookName == curr->bookName
        if(curr->left == nullptr && curr->right == nullptr) {
            delete curr;
            curr = nullptr;
        } else if(curr->left && curr->right == 0) {
            Book *temp = curr->left;
            delete curr;
            curr = temp;
        } else if(curr->left == 0 && curr->right) {
            Book *temp = curr->right;
            delete curr;
            curr = temp;
        } else {
            Book* temp = minHelper(curr->right);
            curr->bookName = temp->bookName;
            curr->author = temp->author;
            curr->rating = temp->rating;
            BookCollection::removeHelper(curr->right, curr->bookName);
        }
    }
}

Book* BookCollection::minHelper(Book* curr) {
    if (!(curr)) {
        return nullptr;
    } else if (curr->left == 0) {
        return curr;
    } else {
        return minHelper(curr->left);
    }
}
 
void BookCollection::rotateHelp(Book *curr,Book *parent, string bookName) {
    if(!(curr)) {
        return;
    }
    if(bookName == curr->bookName && !(curr->right)) {
        return;
    } else if(bookName < curr->bookName) {
        parent = curr;
        rotateHelp(curr->left,parent,bookName);
        return;
    } else if(bookName > curr->bookName) {
        parent = curr;
        rotateHelp(curr->right,parent,bookName);
        return;
    } else { // bookName == curr->bookName
        Book *y = curr->right;
        curr->right = y->left;
        y->left = curr;
        if(curr->bookName < parent->bookName) {
            parent->left = y;
        }
        if(curr->bookName > parent->bookName) {
            parent->right = y;
        }
        return;
    }
}

void BookCollection::rotateLeftCollection(string bookName) {
    if(bookName == "") {
        return;
    } else if(!(root)) {
        return;
    } else if(bookName == root->bookName && root->right) {
        Book *temp = root;
        root = root->right;
        temp->right = root->left;
        root->left = temp;
    } else {
        rotateHelp(root,root,bookName);
    }
}

void BookCollection::closestHelper(Book *curr, string bookName, vector<string>& family) {
    if(!(curr)) {
        cout << "Book not found!" << endl;
        family.clear();
        return;
    } else if(bookName < curr->bookName) {
        family.push_back(curr->bookName);
        BookCollection::closestHelper(curr->left,bookName,family);
    } else if(bookName > curr->bookName) {
        family.push_back(curr->bookName);
        BookCollection::closestHelper(curr->right,bookName,family);
    } else { // bookName == curr->bookName
        family.push_back(curr->bookName);
        return;
    }
}

string BookCollection::closestParent(string book1, string book2) {
    BookCollection::closestHelper(root,book1,family1);
    string parent = "";
    if(family1.size() == 0) {
        parent = "Error - wrong book name";
        return parent;
    }
    BookCollection::closestHelper(root,book2,family2);

    int size = 0;
    if(family1.size() > family2.size()) {
        size = family2.size();
    } else {
        size = family1.size();
    }

    if(size == 0) {
        parent = "Error - wrong book name";
    } else if(size == 1) {
        parent = family1.at(0);
    }
    
    for(int i = 0; i < size; i++) {
        if(family1.at(i) == family2.at(i)) {
            // do nothing;
        } else {
            parent = family1.at(i-1);
            break;
        }
    }

    if(parent == "") {
        parent = family1.at(size-1);
    }

    family1.clear(); family2.clear();
    return parent;
}
