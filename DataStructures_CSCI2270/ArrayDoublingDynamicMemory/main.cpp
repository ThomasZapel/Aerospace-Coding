#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../code/array_double.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 6) {
        cout << "Usage: ./run_app <inputfilename> <Query_Location> <Query_Variant> <Query_Start_Age> <Query_End_Age>" << endl;
        return -1;
    }

    int arrCapacity = 10;
    int DoubleCount = 0;
    int recordIdx = 0;
    CovidCase *cases = new CovidCase[arrCapacity];

    string args[argc];

    for(int i = 0; i < argc; i ++) {
        args[i] = argv[i];
    }

    ifstream inFile;
    inFile.open(argv[1]);

    parseFile(inFile,args,*&cases,arrCapacity,recordIdx,DoubleCount);

    inFile.close();

    sortCases(cases,recordIdx);

    

    cout << "Array doubled: " << DoubleCount << "\n";
    cout << "Total number of cases returned after the query: " << recordIdx << "\n";


    

    printQueriedCases(cases,recordIdx);

    
    return 0;
}