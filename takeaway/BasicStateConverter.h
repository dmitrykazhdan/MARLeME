#ifndef BasicStateConverter_H
#define BasicStateConverter_H

#include "StateConverter.h"
#include "BasicValueExtractor.h"

// This basic state converter takes a set of states, then returns
// a vector of values that consists of values in states[keyID], followed
// by the values returned by the valueExtractor of the remaining states:
// [state1, state2, ..., stateN] --> 
//        states[keyID] + extractedVals(states[0]) + extractedVals(states[1]) + ...
class BasicStateConverter : public StateConverter {
public:
    BasicStateConverter(int _keyID, BasicValueExtractor _valueExtractor);
    void convert(vector<vector<double>> &states, vector<double> &values);
private:
    int keyID;
    BasicValueExtractor valueExtractor;
};


#endif