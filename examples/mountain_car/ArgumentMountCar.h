#ifndef ArgumentMountCar_H
#define ArgumentMountCar_H

#include "ActionArgument.h"

class ArgumentMountCar : public ActionArgument {

public:
    ArgumentMountCar(int _argID, int _agentID, int _action, 
                    double _pos_ub, double _pos_lb, 
                    double _vel_ub, double _vel_lb);
                    
    bool isApplicable(vector<double> &state);
    unique_ptr<ActionArgument> clone() const;
    
private:
    double pos_ub;
    double pos_lb; 
    double vel_ub;
    double vel_lb;
};


#endif
