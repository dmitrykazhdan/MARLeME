#ifndef AgentModel_H
#define AgentModel_H

#include <vector>

using namespace std;

/*
Abstract class used to implement the behaviour of a single extracted model.
The model takes a state as input, and returns a vector output.

'state' - a vector containing agent state information
'output' - a vector containing returned values (e.g. an action, a set of q-values,
            a probability distribution etc.)

*/

class AgentModel {
    virtual void processState(vector<double> &state, vector<double> &output) = 0;
};

#endif
