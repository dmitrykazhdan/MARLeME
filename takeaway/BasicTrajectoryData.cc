#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include "BasicTrajectoryData.h"

using namespace std;

BasicTrajectoryData::BasicTrajectoryData(
    int _numAgents,
    int _numStateVars, 
    int _numOutputVars,
    vector<string> &_stateFilePaths, 
    vector<string> &_actionFilePaths) :
    
    numStateVars(_numStateVars),
    numOutputVars(_numOutputVars), 
    stateFilePaths(_stateFilePaths), 
    actionFilePaths(_actionFilePaths) 
{

    numAgents = _numAgents;
}

void BasicTrajectoryData::processStates(StateProcessor &processor) {

    // Create streams for reading trajectories for every agent
    vector<unique_ptr<ifstream>> stateFileStreams;
    vector<unique_ptr<ifstream>> actionFileStreams;

    for (int i = 0; i < stateFilePaths.size(); i++) {
        stateFileStreams.push_back(make_unique<ifstream>(stateFilePaths.at(i), ios::in));
        actionFileStreams.push_back(make_unique<ifstream>(actionFilePaths.at(i), ios::in));
    }

    // Incrementally process trajectories 
    vector<vector<double>> agentStates(numAgents);
    vector<vector<double>> agentActions(numAgents);

    for (int i = 0; i < numAgents; i++) {
        agentStates.at(i).resize(numStateVars);
        agentActions.at(i).resize(numOutputVars);
    }

    while (readNextStep(agentStates, agentActions, stateFileStreams, 
    actionFileStreams, numStateVars, numOutputVars)) {
        
        processor.processStates(agentStates, agentActions);
    }
}


// Reads the next set of states and actions for a group of agents
// from the given state/action filestreams
bool BasicTrajectoryData::readNextStep(vector<vector<double>> &agentStates,
                  vector<vector<double>> &agentActions,
                  vector<unique_ptr<ifstream>> &stateFileStreams,
                  vector<unique_ptr<ifstream>> &actionFileStreams,
                  int numStateVars,
                  int numOutputVars) {
         
    double val = 0;

    for (int agentID = 0; agentID < stateFileStreams.size(); agentID++) {

        string state_line = "";

        // Stop reading when reached the end of at least one of the files
        if (!getline(*stateFileStreams.at(agentID), state_line)) {
            return false;
        }

        stringstream state_stream(state_line);

        for (int i = 0; i < numStateVars; i++) {
            state_stream >> val;
            agentStates.at(agentID).at(i) = val;
        }

        string action_line = "";

        if (!getline(*actionFileStreams.at(agentID), action_line)) {
            return false;
        }

        stringstream action_stream(action_line);

        for (int i = 0; i < numOutputVars; i++) {
            action_stream >> val;
            agentActions.at(agentID).at(i) = val;
        }
    }
    return true;
}