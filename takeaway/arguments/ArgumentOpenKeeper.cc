
#include "ArgumentOpenKeeper.h"

ArgumentOpenKeeper::ArgumentOpenKeeper(int _argID, int _agentID, int _action, int _numT, int _numK) 
: ActionArgument(_argID, _agentID, _action, _numT, _numK) {

}

// IF min_ang(K_action, T) >= 15

bool ArgumentOpenKeeper::isApplicable(vector<double> &state) {

    int offset = numKeepers + (numTakers - 1) + 
                    (numKeepers - 1) + (numKeepers - 1) +
                    (numTakers - 1);
    offset += action-1;
    
    return state.at(offset) >= 15.0;  
}


unique_ptr<ActionArgument> ArgumentOpenKeeper::clone() const {
  return make_unique<ArgumentOpenKeeper>(
      argID, agentID, action, numTakers, numKeepers); 
}

