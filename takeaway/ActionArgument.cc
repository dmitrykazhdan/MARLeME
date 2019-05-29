#include "ActionArgument.h"

ActionArgument::ActionArgument(int _argID, int _agentID, int _action, int _numT, int _numK) :
argID(_argID), agentID(_agentID), action(_action), numTakers(_numT), numKeepers(_numK) {
}

int ActionArgument::getConclusion() {
    return action;
}

int ActionArgument::getArgID() {
    return argID;
}

int ActionArgument::getAgentID() {
    return agentID;
}

void ActionArgument::setAgentID(int _agentID) {
    agentID = _agentID;
}



