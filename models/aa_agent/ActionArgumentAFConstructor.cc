#include "ActionArgumentAFConstructor.h"


void ActionArgumentAFConstructor::constructAF(
        set<int> &argIDs, 
        const vector<unique_ptr<ActionArgument>> &actionArgsTable, 
        ArgumentationFramework &af) {


    vector<int> vecArgs;

    // Add all arguments to the AF
    for (auto argID : argIDs) {
        af.allArguments.insert(argID);
        vecArgs.push_back(argID);

        set<int> emptySet1;
        set<int> emptySet2;
        af.attacks.insert({argID, emptySet1});
        af.isAttackedBy.insert({argID, emptySet2});
    }

    int arg1 = 0;
    int arg2 = 0;
    int ID1 = 0;
    int ID2 = 0;
    int action1 = 0;
    int action2 = 0;
    bool sameAgent = 0;
    bool sameAction = 0;

    // Consider all unique pairs of arguments
    for (int i = 0; i < vecArgs.size(); i++) {
        for (int j = i; j < vecArgs.size(); j++) {

            arg1 = vecArgs.at(i);
            arg2 = vecArgs.at(j);
            ID1 = actionArgsTable.at(arg1)->getAgentID();
            ID2 = actionArgsTable.at(arg2)->getAgentID();
            action1 = actionArgsTable.at(arg1)->getConclusion();
            action2 = actionArgsTable.at(arg2)->getConclusion();
            sameAgent = (ID1 == ID2);
            sameAction = (action1 == action2);

            // Insert attack between two arguments iff:
            // They recommend the same action to different agents, or
            // they recommend different actions to the same agent
            if ((sameAgent && !sameAction) || (!sameAgent && sameAction)) {
                af.attacks[arg1].insert(arg2);
                af.isAttackedBy[arg2].insert(arg1);
                af.attacks[arg2].insert(arg1);
                af.isAttackedBy[arg1].insert(arg2);              
            }
        }
    }
}
