#include <iostream>
#include <fstream>
#include "../code/fundamentals.hpp"
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    // Inserting from file, sorting, and displaying data
    // stored in array of structs

    // check for number of arguments
    if (argc < 2)
    {
        cout << "file name missing" << endl;
        return -1;
    }

    string filename = argv[1];
    string outfile = argv[2];
    string company, line;
    double stock_price[5];
    stockInfo stocks[4]; 

    ifstream inFile;
    inFile.open(filename);
    int count = 0;

    while(getline(inFile, line)) {
        stringstream csvStream(line);
        string tmp;

        getline(csvStream, company, ',');
        getline(csvStream, tmp, ',');
        stock_price[0] = stod(tmp);
        getline(csvStream, tmp, ',');
        stock_price[1] = stod(tmp);
        getline(csvStream, tmp, ',');
        stock_price[2] = stod(tmp);
        getline(csvStream, tmp, ',');
        stock_price[3] = stod(tmp);
        getline(csvStream, tmp, ',');
        stock_price[4] = stod(tmp);

        insertStockInfo(stocks, company, stock_price, count);

        count++;

    }
    inFile.close();


    ofstream myFile;
    myFile.open(outfile);
    
    for(int i = 0; i < count; i++) {
        displaySortedStocks(stocks[i], myFile); 
    }
    
    
    myFile.close();
    
    
    return 0;
}