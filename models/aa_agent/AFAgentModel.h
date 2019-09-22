#ifndef BasicAgentModel_H
#define BasicAgentModel_H

#include <memory>
#include <set>
#include "AgentModel.h"
#include "ActionArgument.h"
#include "Ordering.h"
#include "StateConverter.h"
#include "VAFConstructor.h"
#include "BasicValueExtractor.h"

/*

Abstract Argumentation based model.

This model communicates state information with other agents, derives applicable
arguments from the received information, constructs an AF from these arguments,
and computes an action from that AF.
*/

class AFAgentModel : public AgentModel {

public:
    AFAgentModel(
        int _agentID,
        vector<int> &_teamIDs,
        string &_agentStateFile,
        string &_agentArgFile,
        vector<string> &_teamStateFiles,
        vector<string> &_teamArgFiles,
        const vector<unique_ptr<ActionArgument>> &_actionArgsTable,
        unique_ptr<BasicValueExtractor> _myConverter,
        Ordering &_argOrdering);

    void processState(vector<double> &state, vector<double> &output);
    void saveOrdering(string &outputFilepath);
    int getNumArgs();

    Ordering argOrdering;

private:
    int agentID;
    vector<int> teamIDs;
    string agentStateFile;
    string agentArgFile;
    vector<string> teamStateFiles;
    vector<string> teamArgFiles;
    vector<unique_ptr<ActionArgument>> actionArgsTable;
    unique_ptr<BasicValueExtractor> myConverter;

    int getActionFromGE(int defaultAction, set<int> &groundedExtension);
    void writeData(vector<double> &state);
    void readData(vector<double> &values);
};


#endif
