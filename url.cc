#include <iostream>
#include <string>
#include <fstream>
#include "clean_url.h"

using namespace std;

/**
* To compile run 'g++ url.cc clean_url.h -o url'
* To run program ./url [input_file.txt] [output_file.txt]
*  Default file names if run with no params are "url_inputs.txt" and "url_results.txt"
*/
int main(int argc, char* argv[])
{
    string input_file = "url_inputs.txt";
    if(argc >= 2) {
        input_file = argv[1];
    }
    // Could stat() and check if file exists here
    string output_file = "url_results.txt";
    if(argc >= 3) {
        output_file = argv[2];
    }

    ifstream infile;
    infile.open(input_file.c_str());
    if(!infile.is_open()) {
        cerr << "Failed to open input file: " << input_file << endl;
        return 1;
    }

    ofstream outfile;
    outfile.open(output_file.c_str(), ios::out | ios::trunc);
    if(!outfile.is_open()) {
        cerr << "Failed to open output file for writting" << endl;
        return 2;
    }

    while(infile.good()) 
    {
        // input files have two columns, separated by single tab only
        //  hence we can use '>>' for extraction
        string input, expected;
        infile >> input;
        if(!infile.good()) break;
        infile >> expected;

        string result = clean_url(input);
        if(expected == result) {
            cout << "Passed: " << input << "\n\t\t --> " << expected << endl;
            outfile << "Passed: " << input << "\n\t\t --> " << expected << endl;
        }
        else {
            cout << "Failed: " << input << "\n\t\t --> " << result << endl;
            outfile << "Failed: " << input << "\n\t\t --> " << result 
                    << "\n\t\tExpected:" << expected << endl;
        }
    }
    

    return 0;
}
