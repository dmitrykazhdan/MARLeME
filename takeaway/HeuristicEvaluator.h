#ifndef HeuristicEvaluator_H
#define HeuristicEvaluator_H

#include <memory>
#include <vector>
#include <map>
#include "StateProcessor.h"
#include "ArgPreferenceGraph.h"
#include "Argument.h"
#include "ActionArgument.h"
#include "BasicValueExtractor.h"


/*
This class computes the applicability and usage metrics of a set of arguments, and is
used to evaluate the quality of argument heuristics.
*/
class HeuristicEvaluator : public StateProcessor {

public:
    HeuristicEvaluator(BasicValueExtractor &_valueExtractor, int numAgents, vector<unique_ptr<ActionArgument>> &_allActionArguments);
    void processStates(vector<vector<double>> &states, vector<vector<double>> &actions);
    void printStats(); 
private:
    vector<unique_ptr<ActionArgument>> allActionArguments;
    vector<double> matches;
    vector<double> misMatches;
    vector<double> numUses;
    vector<double> numMisuses;
    void getApplicableArguments(int agentID, vector<double> &state, vector<int> &applicableArguments);    
    void updateArgs(vector<vector<double>> &actions,  
                vector<int> &applicableArgIDs);   
    BasicValueExtractor valueExtractor;
};

#endif