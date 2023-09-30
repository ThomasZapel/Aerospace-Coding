#include<iostream>
#include<fstream>
#include<cmath>
#include<iomanip>
#include "../code/MessageDecoder.hpp"

using namespace std;


int main(int argc, char* argv[])
{
   if (argc < 2) {
        cout << "Usage: ./run_app <inputfilename>" << endl;
        return 0;
    } else {
        ifstream myFile;
        myFile.open(argv[1]);
        if(!myFile.is_open()) {
          cout << "Error: Could not open file.\n";
          return 0;
        }
        string jumbled_str, postfix;
        int answer;
        getline(myFile, jumbled_str);
        MessageDecoder decoder;
        decoder.generate_operator_queue(jumbled_str);
        postfix = decoder.generate_postfix(jumbled_str);
        answer = decoder.evaluate_postfix(postfix);

        cout << "Postfix Notation::" << postfix << endl;
        cout << "Final Answer::" << answer << endl;


        return 0;
    }
    
  return 0;
}