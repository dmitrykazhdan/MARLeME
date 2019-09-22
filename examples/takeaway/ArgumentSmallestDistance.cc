#include "ArgumentSmallestDistance.h"

ArgumentSmallestDistance::ArgumentSmallestDistance(int _argID, int _agentID, int _action, int _numT, int _numK) 
: ActionArgument(_argID, _agentID, _action, _numT, _numK) {

}

// IF Me = min_dist(K_action, T)

bool ArgumentSmallestDistance::isApplicable(vector<double> &state) {
    
    int offset = action;
    double myDist = state.at(offset);

    offset = numKeepers + (numTakers - 1) + (numKeepers - 1) + (numKeepers - 1) +
                    (numTakers - 1) + (numKeepers - 1);
    

    offset += action;
    double dist;

    for (int i = 0; i < numTakers - 1; i++) {
        dist = state.at(offset + i*numKeepers);

        if (dist < myDist) {
            return false;
        }
    }
    return true;
}


unique_ptr<ActionArgument> ArgumentSmallestDistance::clone() const {
  return make_unique<ArgumentSmallestDistance>(
      argID, agentID, action, numTakers, numKeepers); 
}
