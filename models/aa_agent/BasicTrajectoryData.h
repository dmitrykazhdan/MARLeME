#ifndef BasicTrajectoryData_H
#define BasicTrajectoryData_H

#include "TrajectoryData.h"
#include <string>
#include <memory>

using namespace std;

/*
This class assumes trajectories are stored in text files, with one state file per agent
and one action file per agent.
The states are processes sequentially.
*/
class BasicTrajectoryData : public TrajectoryData {

public:
    BasicTrajectoryData(int _numAgents, int _numStateVars, 
    int _numOutputVars, vector<string> &_stateFilePaths, 
    vector<string> &_actionFilePaths);
    
    void processStates(StateProcessor &processor);
private:
    int numStateVars;
    int numOutputVars;
    vector<string> stateFilePaths;
    vector<string> actionFilePaths;

    bool readNextStep(vector<vector<double>> &agentStates,
                  vector<vector<double>> &agentActions,
                  vector<unique_ptr<ifstream>> &stateFileStreams,
                  vector<unique_ptr<ifstream>> &actionFileStreams,
                  int numStateVars,
                  int numOutputVars);
};


#endif