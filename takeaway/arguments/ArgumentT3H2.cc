#include "ArgumentT3H2.h"

ArgumentT3H2::ArgumentT3H2(int _argID, int _agentID, int _action, int _numT, int _numK) 
: ActionArgument(_argID, _agentID, _action, _numT, _numK) {
}

// IF dist(K1, Me) > 27

bool ArgumentT3H2::isApplicable(vector<double> &state) {

    double dist = state.at(0);

    if (dist >= 27.0) {
        return true;
    } else {
        return false;
    }
}


unique_ptr<ActionArgument> ArgumentT3H2::clone() const {
  return make_unique<ArgumentT3H2>(
      argID, agentID, action, numTakers, numKeepers); 
}




