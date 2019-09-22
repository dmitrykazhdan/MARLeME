#include <sstream>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include "IOUtils.h"


// Save vector of values to specified file.
void IOUtils::saveValues(string &output_filepath, vector<double> &values) {

    string content = "";

    // All values are saved on one line, separated by spaces.
    for (int i = 0; i < values.size(); i++) {
        content += to_string(values.at(i)) + " ";
    }

    ofstream file(output_filepath);
    if (file.is_open()) {
        file << content;
        file.close();
    } 
}


// Load values from a specified file into a vector.
void IOUtils::loadValues(string &file_path, vector<double> &values) {

    ifstream file(file_path, ios::in);
    string line;
    double val;

    // Loads a single line, where values are assumed to be separated by spaces.
    if (getline(file, line)) {
        stringstream file_stream(line);
        file.close();
        
        while (file_stream >> val){
            values.push_back(val);
        }
    }
}



// Saves a set of argument IDs to a specified file.
void IOUtils::saveActionArguments(string &output_filepath, set<int> &argIDs) {

    // Write new file contents
    ofstream ofs;
    ofs.open(output_filepath, ofstream::out | ofstream::trunc);

    // Saves every argument ID on a new line.
    for (auto argID: argIDs) {
        ofs << argID << endl;
    }
    ofs.close();
}

// Reads a set of argument IDs from a specified file.
void IOUtils::readActionArguments(string &input_filepath, set<int> &argIDs) {

    ifstream file(input_filepath, ios::in);
    string line;
    int argID;

    // Assumes every argument ID is stored on a separate line.
    while (getline(file, line)) {
        stringstream file_stream(line);
        file_stream >> argID;
        argIDs.insert(argID);
    }
    file.close();
}









