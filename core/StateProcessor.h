#ifndef StateProcessor_H
#define StateProcessor_H

#include <vector>

using namespace std;

/*
Abstract class representing task-specific state processing behaviour.
*/

class StateProcessor {

public:
    virtual void processStates(vector<vector<double>> &states, vector<vector<double>> &outputs) = 0;
};

#endif
