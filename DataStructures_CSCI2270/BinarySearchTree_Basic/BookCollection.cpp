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

void BookCollection::addBook(string bookName, string author, double rating) {
    if(bookName.empty() || author.empty()) {
        return;
    }

    Book *book = new Book(bookName,author,rating);
    book->bookName = bookName;
    book->author = author;
    book->rating = rating;
    if(root == 0) {
        root = book;
        return;
    } else if(root->left == 0 & book->bookName < root->bookName) {
        root->left = book;
        return;
    } else if(root->right == 0 & book->bookName > root->bookName) {
        root->right = book;
        return;
    }

    if(book->bookName < root->bookName) {
        BookCollection::addHelp(root->left,book);
    } else {
        BookCollection::addHelp(root->right,book);
    }
}

void BookCollection::addHelp(Book *T, Book *book) {
    if(book->bookName < T->bookName) {
        if(T->left != 0) {
            BookCollection::addHelp(T->left,book);
        } else {
            T->left = book;
            return;
        }
    } else {
        if(T->right != 0) {
            BookCollection::addHelp(T->right,book);
        } else {
            T->right = book;
            return;
        }
    }
}

void BookCollection::showBookCollection() {
    if(root == 0) {
        cout << "Collection is empty." << endl;
        return;
    }
    BookCollection::inorderHelp(root);
}

void BookCollection::inorderHelp(Book *book) {
    if(book) {
        BookCollection::inorderHelp(book->left);
        cout << "BOOK: " << book->bookName << " BY: " << book->author << " RATING: " << book->rating << endl;
        BookCollection::inorderHelp(book->right);
    }
}


void BookCollection::showBook(string bookName) {
    if(!(root)) {
        cout << "Book not found." << endl;
        return;
    }
    BookCollection::showBookHelp(bookName,root);
}

void BookCollection::showBookHelp(string bookName, Book *curr) {
    if(bookName == curr->bookName) {
        cout << "Book:" << endl;
        cout << "==================" << endl;
        cout << "Name :" << curr->bookName << endl;
        cout << "Author :" << curr->author << endl;
        cout << "Rating :" << curr->rating << endl;
        return;
    } else if (bookName < curr->bookName && curr->left) {
        BookCollection::showBookHelp(bookName,curr->left);
        return;
    } else if (bookName > curr->bookName && curr->right) {
        BookCollection::showBookHelp(bookName,curr->right);
        return;
    } else {
        cout << "Book not found." << endl;
        return;
    }
}

void BookCollection::showBooksByAuthor(string author) {
    cout << "Books By: " << author << endl;
    BookCollection::showBooksByAuthorHelp(author,root);
}

void BookCollection::showBooksByAuthorHelp(string author, Book *curr) {
    if(curr) {
        BookCollection::showBooksByAuthorHelp(author,curr->left);
        if(author == curr->author) {
            cout << curr->bookName << " RATING: " << curr->rating << endl;
        }
        BookCollection::showBooksByAuthorHelp(author,curr->right);
    }
}

void BookCollection::showHighestRatedBooks() {
    if(!(root)) {
        cout << "Collection is empty." << endl;
    } else {
        double maxRate = BookCollection::HighestRateHelp(root,root->rating);
        cout << "Highest Rating: " << maxRate << endl;
        BookCollection::showHighestRatedBooksHelp(root,maxRate);
    }
    return;
}

double BookCollection::HighestRateHelp(Book *curr,double rate) {
    if(curr) {
        rate = BookCollection::HighestRateHelp(curr->left,rate);
        if(curr->rating > rate) {
            rate = curr->rating;
        } else {
            // do nothing
        }
        rate = BookCollection::HighestRateHelp(curr->right,rate);
    }
    return rate;
    
}

void BookCollection::showHighestRatedBooksHelp(Book *curr,double maxRate) {
    if(curr) {
        BookCollection::showHighestRatedBooksHelp(curr->left,maxRate);
        if(maxRate == curr->rating) {
            cout << curr->bookName << " BY: " << curr->author << endl;
        }
        BookCollection::showHighestRatedBooksHelp(curr->right,maxRate);
    }
}

int BookCollection::getHeightOfBookCollection() {
    int height = 0;
    height = BookCollection::getHeightHelp(root);
    return height;
}

int BookCollection::getHeightHelp(Book *curr) {
    if(!(curr)) {
        return 0;
    } else {
        int left = BookCollection::getHeightHelp(curr->left);
        int right = BookCollection::getHeightHelp(curr->right);
        if(right > left) {
            return ++right;
        } else {
            return ++left;
        }
    }
}