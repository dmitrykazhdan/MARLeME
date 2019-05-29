#ifndef TrajectoryData_H
#define TrajectoryData_H

#include <vector>
#include "StateProcessor.h"

using namespace std;


/*
Abstract class encapsulating information about trajectory data.
This may include the types of data (text, databases, json etc.), and data handling behaviour.

Includes a `processStates' method that handles data loading, pre-processing, parsing etc.
Before passing it to a state processor that applies task-specific processing to the state information.
*/
class TrajectoryData {

public:
    int numAgents;
    virtual void processStates(StateProcessor &processor) = 0;
};


#endif