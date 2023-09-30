#include "array_double.hpp"
#include <sstream>

using namespace std;

void parseFile(ifstream& input,string queryParams[], CovidCase *&cases, int &arrCapacity,  int &recordIdx, int &doublingCounter) {
    string queryLocation = queryParams[2];
    string queryVariant = queryParams[3];
    int startAge = stoi(queryParams[4]);
    int endAge = stoi(queryParams[5]);
    string line;

    while(getline(input, line)) {

        stringstream stream(line);
        string name,location,variant,tmpAge;
        int age;

        // name, variant, location, age
        getline(stream, name, ',');
        getline(stream, variant, ',');
        getline(stream, location, ',');
        getline(stream, tmpAge);
        age = stoi(tmpAge);

        CovidCase temp;
        temp.name = name;
        temp.variant = variant;
        temp.location = location;
        temp.age = age;

        // Check if values match query
        if(isCaseQueried(temp,queryLocation,queryVariant,startAge,endAge)) {
            // then add the temp values into the array of structs
            addCase(*&cases, temp, arrCapacity,recordIdx,doublingCounter);
            //                          ^10          ^0         ^0
            
        }

        
    }


}

bool isCaseQueried(CovidCase covidCase, string queryLocation, string queryVariant, int startAge, int endAge) {
    if(covidCase.location == queryLocation && covidCase.variant == queryVariant && covidCase.age >= startAge && covidCase.age <= endAge) {
        return true;
    }

    
    return false;
}

void resizeArr(CovidCase *&cases, int *arraySize) {
    CovidCase *temp = new CovidCase[*arraySize * 2];

    for(int i = 0; i < *arraySize; i++) {
        temp[i] = cases[i];
    }

    delete[] cases;
    cases = temp;

    *arraySize = *arraySize * 2;
 
}

void addCase(CovidCase *&cases, CovidCase covidCase, int &arrCapacity, int &recordIdx, int &doublingCounter) {
    // if the index of the new entry is equal to or greater than the capacity then resize the array
    if(arrCapacity <= recordIdx) {
        int *arraySize = &arrCapacity;
        resizeArr(*&cases,arraySize);
        doublingCounter++;
    } // Now array will have capacity for the new entry

    cases[recordIdx] = covidCase;

    recordIdx++;

}

void sortCases(CovidCase* cases, int length) {
    int temp;
    string stemp;

    // Bubble sort based on age
    for(int i = 0; i < length; i++) {
        for(int j = i + 1; j < length; j++) {
            if(cases [j].age < cases [i].age) {
                temp = cases [i].age;
                cases [i].age = cases [j].age;
                cases [j].age = temp;

                stemp = cases [i].name;
                cases [i].name = cases [j].name;
                cases [j].name = stemp;

                stemp = cases [i].location;
                cases [i].location = cases [j].location;
                cases [j].location = stemp;

                stemp = cases [i].variant;
                cases [i].variant = cases [j].variant;
                cases [j].variant = stemp;
            } else if(cases [j].age == cases [i].age) {
                // sort alphabetically
                if(cases [j].name < cases [i].name) {
                    stemp = cases [i].name;
                    cases [i].name = cases [j].name;
                    cases [j].name = stemp;

                    stemp = cases [i].location;
                    cases [i].location = cases [j].location;
                    cases [j].location = stemp;

                    stemp = cases [i].variant;
                    cases [i].variant = cases [j].variant;
                    cases [j].variant = stemp;
                }
            }
        }
    } 
}

void printQueriedCases(CovidCase* cases, int numOfRecords) {
    cout << "Queried Cases" << "\n" << "---------------------------------------" << "\n";
    for(int i = 0; i < numOfRecords; i++) {
        cout << cases [i].name << " " << cases [i].age << "\n";
    }

}