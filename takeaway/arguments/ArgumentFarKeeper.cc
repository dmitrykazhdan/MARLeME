#include "ArgumentFarKeeper.h"

ArgumentFarKeeper::ArgumentFarKeeper(int _argID, int _agentID, int _action, int _numT, int _numK) 
: ActionArgument(_argID, _agentID, _action, _numT, _numK) {

}

// IF min dist(K_action, T) >= 10

bool ArgumentFarKeeper::isApplicable(vector<double> &state) {
    
    double myDist = state.at(action);

    if (myDist >= 10) {
        return true;
    }

    int offset = numKeepers + (numTakers - 1) + (numKeepers - 1) + 
                    (numKeepers - 1) +
                    (numTakers - 1) + (numKeepers - 1);

    offset += action; 
    double dist;

    for (int i = 0; i < numTakers-1; i++) {
        dist = state.at(offset + i*numKeepers);

        if (dist >= 10) {
            return true;
        }
    }
    return false; 
}

unique_ptr<ActionArgument> ArgumentFarKeeper::clone() const {
  return make_unique<ArgumentFarKeeper>(
      argID, agentID, action, numTakers, numKeepers); 
}


