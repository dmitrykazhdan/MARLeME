#include "BasicStateProcessor.h"
#include "ActionArgument.h"
#include "BasicStateConverter.h"
#include <iostream>

using namespace std;



BasicStateProcessor::BasicStateProcessor(
    BasicValueExtractor &_valueExtractor,
    int numAgents,
    vector<unique_ptr<ActionArgument>> &_allActionArguments) : 
    valueExtractor(_valueExtractor),
    allActionArguments(),
    preferenceGraph()
{

    for (int i = 0; i < _allActionArguments.size(); i++) {
        unique_ptr<ActionArgument> argPtr = _allActionArguments.at(i)->clone();
        allActionArguments.push_back(move(argPtr));
    }

    set<int> allArgIDs;
    for (int i = 0; i < allActionArguments.size(); i++) {
        allArgIDs.insert(allActionArguments.at(i)->getArgID());
    }

    preferenceGraph.initialize(allArgIDs);
}


// Compute all applicable arguments from given set of states
// Update the preference graph using these arguments
void BasicStateProcessor::processStates(vector<vector<double>> &states, vector<vector<double>> &actions) {
    
    vector<int> applicableArgIDs;

    for (int agentID = 0; agentID < states.size(); agentID++) {
        BasicStateConverter converter(agentID, valueExtractor);
        vector<double> values;
        converter.convert(states, values);
        getApplicableArguments(agentID, values, applicableArgIDs);
    }
    updatePrefGraph(actions, applicableArgIDs, preferenceGraph);
}

// Increment edges between all pairs of arguments (A, B), 
// where A recommends the correct action, and B does not.
void BasicStateProcessor::updatePrefGraph(vector<vector<double>> &actions,  
                vector<int> &applicableArgIDs,
                ArgPreferenceGraph &pref_graph) {

    vector<int> relevantArgIDs;
    vector<int> irrelevantArgIDs;
    int trueAction;
    int agentID;
    int argID;

    for (int i = 0; i < applicableArgIDs.size(); i++) {

        argID = applicableArgIDs.at(i);
        agentID = allActionArguments.at(argID)->getAgentID();
        trueAction = actions.at(agentID).at(0);

        if (allActionArguments.at(argID)->getConclusion() == trueAction) {
            relevantArgIDs.push_back(argID);
        } else {
            irrelevantArgIDs.push_back(argID);
        }
    }
    
    for (auto prefArgID : relevantArgIDs) {
        for (auto nonPrefArgID : irrelevantArgIDs) {
            pref_graph.incrementPreference(prefArgID, nonPrefArgID);
        }
    }
}


// Compute all arguments applicable for a given agent in a given state
// Add instances of these arguments
void BasicStateProcessor::getApplicableArguments(
            int agentID, 
            vector<double> &state, 
            vector<int> &applicableArguments) {

    for (int argID = 0; argID < allActionArguments.size(); argID++) {
        if ((allActionArguments.at(argID)->getAgentID()==agentID) &&
            (allActionArguments.at(argID)->isApplicable(state))) { 
                
            applicableArguments.push_back(argID);
        }
    }
}