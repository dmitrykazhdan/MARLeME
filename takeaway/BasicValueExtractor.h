#include "StateConverter.h"

#ifndef BasicValueExtractor_H
#define BasicValueExtractor_H

// A very basic state converter that accepts a single state vector
// And returns the first numVal elements of this vector as output
class BasicValueExtractor : public StateConverter {
public:
    BasicValueExtractor(int _numVals);
    void convert(vector<vector<double>> &states, vector<double> &values);
    void convert(vector<double> &states, vector<double> &values);
private:
    int numVals;
};


#endif