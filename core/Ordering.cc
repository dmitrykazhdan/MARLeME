#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <set>
#include "Ordering.h"


Ordering::Ordering() : values() {
}

Ordering::Ordering (const Ordering &oldOrdering) : values() {

    for (auto keyValue : oldOrdering.values) {
        values[keyValue.first] = keyValue.second;
    }
}

int Ordering::getValue(int argID) {
    return values[argID];
}

void Ordering::setValue(pair<int, int> keyValuePair) {
    values[keyValuePair.first] = keyValuePair.second;
}

// Loads ordering from file
// Assumes a line contains a key-value pair, separated with a space
void Ordering::loadOrdering(string &file_path) {

    values.clear();

    ifstream file(file_path, ios::in);
    string line;
    int argID = 0;
    int argVal = 0;
    
    while (getline(file, line)) {
        stringstream file_stream(line);
        file_stream >> argID;
        file_stream >> argVal;
        values.insert({argID, argVal});
    }
    file.close();
}


// Saves ordering to a file
// Assumes a line contains a key-value pair, separated with a space
void Ordering::saveOrdering(string &output_filepath) {

    // Sort ordering by value
    typedef function<bool(pair<int, int>, pair<int, int>)> Comparator;

    Comparator compFunctor = 
    [](pair<int, int> elem1, pair<int, int> elem2)
        {
            return elem1.second >= elem2.second;
        };
    
    set<pair<int, int>, Comparator> sortedValues(values.begin(), values.end(), compFunctor);

    ofstream file(output_filepath);

    if (file.is_open()) {
        for (auto keyValue : sortedValues) {
            file << keyValue.first << " " << keyValue.second << endl;
        }
        file.close();
    } else {
        string f_path(output_filepath);
        string err_msg = "Could not open file: " + output_filepath;
        throw runtime_error(err_msg);
    }
}