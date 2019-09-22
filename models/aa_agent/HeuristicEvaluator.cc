#include "HeuristicEvaluator.h"
#include "ActionArgument.h"
#include "BasicStateConverter.h"
#include <iostream>
#include <map>



HeuristicEvaluator::HeuristicEvaluator(
    BasicValueExtractor &_valueExtractor,
    int numAgents,
    vector<unique_ptr<ActionArgument>> &_allActionArguments) : 
    valueExtractor(_valueExtractor),
    allActionArguments()
{

    for (int i = 0; i < _allActionArguments.size(); i++) {
        unique_ptr<ActionArgument> argPtr = _allActionArguments.at(i)->clone();
        allActionArguments.push_back(move(argPtr));
    }

    for (int i = 0; i < allActionArguments.size(); i++) {
        matches.push_back(0);
        misMatches.push_back(0);
        numUses.push_back(0);
        numMisuses.push_back(0);
    }
}


void HeuristicEvaluator::processStates(vector<vector<double>> &states, vector<vector<double>> &actions) {
    
    vector<int> applicableArgIDs;

    for (int agentID = 0; agentID < states.size(); agentID++) {
        BasicStateConverter converter(agentID, valueExtractor);
        vector<double> values;
        converter.convert(states, values);
        getApplicableArguments(agentID, values, applicableArgIDs);
    }
    updateArgs(actions, applicableArgIDs);
}


void HeuristicEvaluator::updateArgs(vector<vector<double>> &actions,  
                vector<int> &applicableArgIDs) {

    int trueAction;
    int agentID;
    int argID;

    for (int i = 0; i < applicableArgIDs.size(); i++) {

        argID = applicableArgIDs.at(i);
        agentID = allActionArguments.at(argID)->getAgentID();
        trueAction = actions.at(agentID).at(0);

        if (allActionArguments.at(argID)->getConclusion() == trueAction) {
            matches.at(argID)++;
        } else {
            misMatches.at(argID)++;
        }
    }
}


// Compute all arguments applicable for a given agent in a given state
// Add instances of these arguments
void HeuristicEvaluator::getApplicableArguments(
            int agentID, 
            vector<double> &state, 
            vector<int> &applicableArguments) {

    for (int argID = 0; argID < allActionArguments.size(); argID++) {
        if (allActionArguments.at(argID)->getAgentID()==agentID) {
            if (allActionArguments.at(argID)->isApplicable(state)) { 
                
                applicableArguments.push_back(argID);
                numUses.at(argID)++;
            } else {
                numMisuses.at(argID)++;
            }
        }
    }
}

void HeuristicEvaluator::printStats() {

    double score;
    double usage;
    int argID;
    map<int, double> scoreMap;
    map<int, double> useMap;

    for (int i = 0; i < misMatches.size(); i++) {
        argID = allActionArguments.at(i)->getArgID();
        score = matches.at(i) / (matches.at(i) + misMatches.at(i)) * 100.0;
        usage = numUses.at(i) / (numUses.at(i) + numMisuses.at(i)) * 100.0;
        scoreMap[argID] = score;
        useMap[argID] = usage;
    }


    typedef function<bool(pair<int, double>, pair<int, double>)> Comparator;

    Comparator compFunctor = 
    [](pair<int, double> elem1, pair<int, double> elem2)
        {
            return elem1.second >= elem2.second;
        };
    
    set<pair<int, double>, Comparator> sortedValues(scoreMap.begin(), scoreMap.end(), compFunctor);

    for (auto keyValue : sortedValues) {
        cout << "Arg " << keyValue.first << " score: " << keyValue.second  
        << " usage: " << useMap[keyValue.first] << endl;
    }
}