#include "BasicValueExtractor.h"
#include <string>
#include <stdexcept>

BasicValueExtractor::BasicValueExtractor(int _numVals) : numVals(_numVals) {
}


// State converter assumes that only a single state is given as input
// Throws an exception otherwise
void BasicValueExtractor::convert(vector<vector<double>> &states, vector<double> &values) {

    if (states.size() != 1) {
        throw runtime_error(string("Error: expecting a 'states' vector of size 1..."));
    }
    convert(states.at(0), values);
}

void BasicValueExtractor::convert(vector<double> &state, vector<double> &values) {

    for (int i = 0; i < numVals; i++) {
        values.push_back(state.at(i));
    }
}