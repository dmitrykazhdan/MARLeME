#include "ArgumentSmallestAngle.h"

ArgumentSmallestAngle::ArgumentSmallestAngle(int _argID, int _agentID, int _action, int _numT, int _numK) 
: ActionArgument(_argID, _agentID, _action, _numT, _numK) {

}

// IF Me = min_ang(K_action, T)

bool ArgumentSmallestAngle::isApplicable(vector<double> &state) {
    
    int offset = numKeepers + (numTakers - 1) + action - 1;
    double myAngle = state.at(offset);

    offset = numKeepers + (numTakers - 1) + (numKeepers - 1) + (numKeepers - 1) +
                    (numTakers - 1);
    offset += action - 1;
    double minAngle = state.at(offset);

    return myAngle <= minAngle;  
}

unique_ptr<ActionArgument> ArgumentSmallestAngle::clone() const {
  return make_unique<ArgumentSmallestAngle>(
      argID, agentID, action, numTakers, numKeepers); 
}

