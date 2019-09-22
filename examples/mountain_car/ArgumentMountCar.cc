#include "ArgumentMountCar.h"

ArgumentMountCar::ArgumentMountCar(int _argID, int _agentID, int _action, 
                    double _pos_ub, double _pos_lb, 
                    double _vel_ub, double _vel_lb) : 
                    ActionArgument(_argID, _agentID, _action), 
                    pos_ub(_pos_ub), pos_lb(_pos_lb), 
                    vel_ub(_vel_ub), vel_lb(_vel_lb) {
}


// Mountain car argument
// The argument is applicable in a given state, if the state
// is within the sub-range specified by the argument
bool ArgumentMountCar::isApplicable(vector<double> &state) {
    
    // Variables of the state
    double pos = state.at(0);
    double vel = state.at(1);

    // Check that both position and velocity are in the
    // ranges specified by the argument
    bool pos_in_range = (pos > pos_lb) && (pos <= pos_ub);
    bool vel_in_range = (vel > vel_lb) && (vel <= vel_ub);

    return (pos_in_range && vel_in_range);
}

unique_ptr<ActionArgument> ArgumentMountCar::clone() const {
  return make_unique<ArgumentMountCar>(
      argID, agentID, action, pos_ub, pos_lb, vel_ub, vel_lb); 
}
