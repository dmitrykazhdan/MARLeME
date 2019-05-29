#include <vector>
#include <memory>
#include <iostream>
#include "AFAgentModel.h"
#include "BasicModelExtractor.h"
#include "ActionArgument.h"
#include "ArgumentationFramework.h"
#include "ActionArgumentAFConstructor.h"
#include "VAFConstructor.h"
#include "Ordering.h"
#include "GESolver.h"
#include "IOUtils.h"


AFAgentModel::AFAgentModel(
        int _agentID,
        vector<int> &_teamIDs,
        string &_agentStateFile,
        string &_agentArgFile,
        vector<string> &_teamStateFiles,
        vector<string> &_teamArgFiles,
        const vector<unique_ptr<ActionArgument>> &_actionArgsTable,
        unique_ptr<BasicValueExtractor> _myConverter,
        Ordering &_argOrdering) :

        agentID(_agentID), teamIDs(_teamIDs), agentStateFile(_agentStateFile),
        agentArgFile(_agentArgFile), teamStateFiles(_teamStateFiles),
        teamArgFiles(_teamArgFiles), actionArgsTable(),
        myConverter(move(_myConverter)), argOrdering(_argOrdering) {


    for (int i = 0; i < _actionArgsTable.size(); i++) {
        unique_ptr<ActionArgument> argPtr = _actionArgsTable.at(i)->clone();
        actionArgsTable.push_back(move(argPtr));
    }
}


void AFAgentModel::processState(vector<double> &old_state, vector<double> &output) {

    vector<double> state(old_state);

    // Send agent state information to other agents in the team
    writeData(state);

    // Receive agent state information from other agents in the team
    readData(state);

    // Compute applicable arguments for the agent
    set<int> applicableArgs;

    for (int i = 0; i < actionArgsTable.size(); i++) {
        if ((actionArgsTable.at(i)->getAgentID()==agentID) &&
            (actionArgsTable.at(i)->isApplicable(state))) {

            applicableArgs.insert(i);
        }
    }

    // Save agent arguments
    IOUtils::saveActionArguments(agentArgFile, applicableArgs);

    // Load other agent arguments
    for (int i = 0; i < teamIDs.size(); i++) {
        IOUtils::readActionArguments(teamArgFiles.at(i), applicableArgs);
    }

    // Construct an Argumentation Framework from the arguments
    ArgumentationFramework af;
    ActionArgumentAFConstructor::constructAF(applicableArgs, actionArgsTable, af);

    // Derive a simplification of the AF, using the argument ordering
    ArgumentationFramework vaf;
    VAFConstructor::constructVAF(af, argOrdering, vaf);

    // Compute the grounded extension from the AF simplification.
    GESolver solver;
    set<set<int>> extensions;
    int defaultAction = -1;
    solver.solve(vaf, extensions);

    // Derive an action from the grounded extension.
    for (auto groundedExtension : extensions) {
        output.push_back(getActionFromGE(defaultAction, groundedExtension));
        return;
    }
}



int AFAgentModel::getActionFromGE(int defaultAction,  set<int> &groundedExtension) {

    int recAction = defaultAction;

    // Assumes that all arguments of the agent recommend the same action.
    for (auto recArgID : groundedExtension) {
        if (actionArgsTable.at(recArgID)->getAgentID() == agentID) {
            recAction = actionArgsTable.at(recArgID)->getConclusion();
            break;
        }
    }
    return recAction;
}


// Converts the data into the format used by the team, before saving it to the file.
void AFAgentModel::writeData(vector<double> &state) {
    vector<double> values;
    myConverter->convert(state, values);
    IOUtils::saveValues(agentStateFile, values);
}

void AFAgentModel::readData(vector<double> &values) {
    for (int i = 0; i < teamStateFiles.size(); i++) {
        IOUtils::loadValues(teamStateFiles.at(i), values);
    }
}

int AFAgentModel::getNumArgs() {
    return actionArgsTable.size();
}

void AFAgentModel::saveOrdering(string &outputPath) {
    argOrdering.saveOrdering(outputPath);
}
