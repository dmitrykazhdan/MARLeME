#include "ArgumentT1H2.h"

ArgumentT1H2::ArgumentT1H2(int _argID, int _agentID, int _action, int _numT, int _numK) 
: ActionArgument(_argID, _agentID, _action, _numT, _numK) {
}


// IF dist(T2, K1) > 26

bool ArgumentT1H2::isApplicable(vector<double> &state) {

    int offset = numKeepers + 
    (numTakers - 1) + (numKeepers - 1) + (numKeepers - 1) + 1;

    double dist = state.at(offset);

    if (dist > 26) {
        return true;
    } else {
        return false;
    }
}


unique_ptr<ActionArgument> ArgumentT1H2::clone() const {
  return make_unique<ArgumentT1H2>(
      argID, agentID, action, numTakers, numKeepers); 
}




