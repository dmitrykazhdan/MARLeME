#include "ArgumentT2H3_T3H1.h"

ArgumentT2H3_T3H1::ArgumentT2H3_T3H1(int _argID, int _agentID, int _action, int _numT, int _numK)
: ActionArgument(_argID, _agentID, _action, _numT, _numK) {
}


// IF dist(K4, K1) > 42

bool ArgumentT2H3_T3H1::isApplicable(vector<double> &state) {

    int offset = numKeepers + (numTakers - 1) + (numKeepers - 1) + 2;
    double dist = state.at(offset);

    if (dist > 42) {
        return true;
    } else {
        return false;
    }
}


unique_ptr<ActionArgument> ArgumentT2H3_T3H1::clone() const {
  return make_unique<ArgumentT2H3_T3H1>(
      argID, agentID, action, numTakers, numKeepers);
}




