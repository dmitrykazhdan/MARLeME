#ifndef BasicStateProcessor_H
#define BasicStateProcessor_H

#include <memory>
#include <vector>
#include <map>
#include "StateProcessor.h"
#include "ArgPreferenceGraph.h"
#include "Argument.h"
#include "ActionArgument.h"
#include "BasicValueExtractor.h"


/*
Constructs an argument preference graph from a set of agent trajectories
*/

class BasicStateProcessor : public StateProcessor {

public:
    BasicStateProcessor(BasicValueExtractor &_valueExtractor, int numAgents, vector<unique_ptr<ActionArgument>> &_allActionArguments);
    void processStates(vector<vector<double>> &states, vector<vector<double>> &actions);
    ArgPreferenceGraph preferenceGraph;
private:
    vector<unique_ptr<ActionArgument>> allActionArguments;
    void getApplicableArguments(int agentID, vector<double> &state, vector<int> &applicableArguments);
    void updatePrefGraph(vector<vector<double>> &actions,  
                vector<int> &applicableArgIDs,
                ArgPreferenceGraph &pref_graph);
    
    BasicValueExtractor valueExtractor;
};

#endif