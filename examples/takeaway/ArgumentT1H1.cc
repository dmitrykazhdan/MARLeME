#include "ArgumentT1H1.h"

ArgumentT1H1::ArgumentT1H1(int _argID, int _agentID, int _action, int _numT, int _numK) 
: ActionArgument(_argID, _agentID, _action, _numT, _numK) {
}


// IF min_ang(K2, T) < 18

bool ArgumentT1H1::isApplicable(vector<double> &state) {

    int offset = numKeepers + (numTakers - 1) + 
                (numKeepers - 1) + (numKeepers - 1) +
                    (numTakers - 1);

    double ang = state.at(offset);

    if (ang < 18) {
        return true;
    } else {
        return false;
    }
}


unique_ptr<ActionArgument> ArgumentT1H1::clone() const {
  return make_unique<ArgumentT1H1>(
      argID, agentID, action, numTakers, numKeepers); 
}




