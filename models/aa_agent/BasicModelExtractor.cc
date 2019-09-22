#include "BasicModelExtractor.h"
#include "StateProcessor.h"
#include "BasicTeamModel.h"
#include "AFAgentModel.h"
#include "BasicStateProcessor.h"
#include "Ordering.h"
#include "OrderingComputation.h"
#include "ArgumentTackle.h"
#include "ArgumentFarKeeper.h"
#include "ArgumentOpenKeeper.h"
#include "ArgumentSmallestAngle.h"
#include "ArgumentSmallestDistance.h"
#include "BasicValueExtractor.h"
#include <iostream>
#include "ArgumentT1H1.h"
#include "ArgumentT1H2.h"
#include "ArgumentT2H1.h"
#include "ArgumentT2H3_T3H1.h"
#include "ArgumentT3H2.h"

using namespace std;


BasicModelExtractor::BasicModelExtractor(int _numK, int _numT,
                        vector<string> &_teamCommState,
                        vector<string> &_teamCommArgs)
: numTakers(_numT), numKeepers(_numK),
teamCommState(_teamCommState), teamCommArgs(_teamCommArgs),
allActionArguments(), default_ordering() {

    loadDefaultArguments();
    loadDefaultOrdering();
}


BasicModelExtractor::BasicModelExtractor(int _numK, int _numT,
            vector<string> &_teamCommState,
            vector<string> &_teamCommArgs,
            const vector<unique_ptr<ActionArgument>> &_allActionArguments,
            Ordering &_default_ordering) :
 numTakers(_numT), numKeepers(_numK),
 teamCommState(_teamCommState), teamCommArgs(_teamCommArgs),
 allActionArguments(), default_ordering(_default_ordering)            {

    for (int i = 0; i < _allActionArguments.size(); i++) {
        unique_ptr<ActionArgument> argPtr = _allActionArguments.at(i)->clone();
        allActionArguments.push_back(move(argPtr));
    }
}


void BasicModelExtractor::splitVec(vector<string> &allVecs, vector<string> &outputVecs, int vecID) {

    for (int i = 0; i < allVecs.size(); i++) {
        if (i != vecID) {
            outputVecs.push_back(allVecs.at(i));
        }
    }
}


TeamModel* BasicModelExtractor::extractModel(TrajectoryData &trajectories, BasicStateProcessor &state_processor) {

    // Compute the argument preference graph from the agent trajectories
    trajectories.processStates(state_processor);

    BasicTeamModel *model = new BasicTeamModel();

    vector<int> teamIDs;

    for (int i = 0; i < numTakers; i++){
        teamIDs.push_back(i);
    }

    Ordering extractedOrdering;

    // Extract the argument ordering from the preference graph.
    OrderingComputation::extractOrdering(
        state_processor.preferenceGraph,
        default_ordering,
        extractedOrdering);

    // Create set of BasicAgentModel agents, and add them to the team.
    for (int agentID = 0; agentID < numTakers; agentID++) {

        string agentStateFile = teamCommState.at(agentID);
        string agentArgFile = teamCommArgs.at(agentID);
        vector<string> teamStateFiles;
        vector<string> teamArgFiles;

        splitVec(teamCommState, teamStateFiles, agentID);
        splitVec(teamCommArgs, teamArgFiles, agentID);

        auto myConverter = make_unique<BasicValueExtractor>(numKeepers);

        auto agent = make_unique<AFAgentModel>(agentID, teamIDs, agentStateFile, agentArgFile, teamStateFiles,
                              teamArgFiles, allActionArguments, move(myConverter), extractedOrdering);

        model->addAgent(move(agent));
    }
    return model;
}


TeamModel* BasicModelExtractor::extractModel(TrajectoryData &trajectories) {
    BasicValueExtractor valueExtractor(numKeepers);
    BasicStateProcessor state_processor(valueExtractor, numTakers, allActionArguments);
    return extractModel(trajectories, state_processor);
}


void BasicModelExtractor::loadDefaultOrdering() {

    int offset = 0;

    for (int j = 0; j < numTakers; j++) {

        default_ordering.setValue({offset++, 5});

        for (int i = 1; i < numKeepers; i++) {
            default_ordering.setValue({offset++, 2});
            default_ordering.setValue({offset++, 1});
            default_ordering.setValue({offset++, 4});
            default_ordering.setValue({offset++, 4});
        }
    }

     default_ordering.setValue({offset++, 6});
     default_ordering.setValue({offset++, 6});
     default_ordering.setValue({offset++, 6});
     default_ordering.setValue({offset++, 6});
     default_ordering.setValue({offset++, 6});
     default_ordering.setValue({offset++, 6});

}


void BasicModelExtractor::loadDefaultArguments() {

    int offset = 0;

    for (int agentID = 0; agentID < numTakers; agentID++) {

        allActionArguments.push_back(make_unique<ArgumentTackle>(offset++, agentID, 0, numTakers, numKeepers));

        for (int i = 1; i < numKeepers; i++) {
            // Create arguments and their values
            allActionArguments.push_back(make_unique<ArgumentOpenKeeper>(offset++, agentID, i, numTakers, numKeepers));
            allActionArguments.push_back(make_unique<ArgumentFarKeeper>(offset++, agentID, i, numTakers, numKeepers));
            allActionArguments.push_back(make_unique<ArgumentSmallestAngle>(offset++, agentID, i, numTakers, numKeepers));
            allActionArguments.push_back(make_unique<ArgumentSmallestDistance>(offset++, agentID, i, numTakers, numKeepers));
        }
    }

    allActionArguments.push_back(make_unique<ArgumentT1H1>(offset++, 0, 0, numTakers, numKeepers));
    allActionArguments.push_back(make_unique<ArgumentT1H2>(offset++, 0, 0, numTakers, numKeepers));
    allActionArguments.push_back(make_unique<ArgumentT2H1>(offset++, 1, 2, numTakers, numKeepers));
    allActionArguments.push_back(make_unique<ArgumentT2H3_T3H1>(offset++, 1, 2, numTakers, numKeepers));
    allActionArguments.push_back(make_unique<ArgumentT2H3_T3H1>(offset++, 2, 3, numTakers, numKeepers));
    allActionArguments.push_back(make_unique<ArgumentT3H2>(offset++, 2, 3, numTakers, numKeepers));

}














