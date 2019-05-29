#include "ArgumentTackle.h"

ArgumentTackle::ArgumentTackle(int _argID, int _agentID, int _action, int _numT, int _numK) 
: ActionArgument(_argID, _agentID, _action, _numT, _numK) {
}


// IF Me = argmin dist(K1, T)

bool ArgumentTackle::isApplicable(vector<double> &state) {

    double myDist = state.at(0);
    double val;
    int offset = numKeepers + (numTakers - 1) + 
                (numKeepers - 1) + (numKeepers - 1);

    for (int i = 0; i < numTakers - 1; i++) {
        val = state.at(offset + i);
        if (val < myDist) {
            return false;
        }
    }
    return true;
}


unique_ptr<ActionArgument> ArgumentTackle::clone() const {
  return make_unique<ArgumentTackle>(
      argID, agentID, action, numTakers, numKeepers); 
}




