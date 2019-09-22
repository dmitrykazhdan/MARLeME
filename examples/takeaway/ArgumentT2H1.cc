#include "ArgumentT2H1.h"

ArgumentT2H1::ArgumentT2H1(int _argID, int _agentID, int _action, int _numT, int _numK)
: ActionArgument(_argID, _agentID, _action, _numT, _numK) {
}

// IF 29 <= dist(K3, K1) <= 35

bool ArgumentT2H1::isApplicable(vector<double> &state) {

    int offset = numKeepers + (numTakers - 1) + (numKeepers - 1) + 1;
    double dist = state.at(offset);

    if (dist >= 29 && dist <= 35) {
        return true;
    } else {
        return false;
    }
}


unique_ptr<ActionArgument> ArgumentT2H1::clone() const {
  return make_unique<ArgumentT2H1>(
      argID, agentID, action, numTakers, numKeepers);
}




