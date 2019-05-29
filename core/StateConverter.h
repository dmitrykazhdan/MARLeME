#ifndef StateConverter_H
#define StateConverter_H


#include <vector>

using namespace std;

/*
A state converter is used to convert one state representation into another.

For example, different agents may represent information in different formats,
and need to convert it appropriately when communicating.

states - original representation consisting of a set of states
values - new representation

*/

class StateConverter {

public:
    virtual void convert(vector<vector<double>> &states, vector<double> &values) = 0;
};

#endif