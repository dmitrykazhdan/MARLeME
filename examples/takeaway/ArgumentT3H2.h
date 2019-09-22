#include "ActionArgument.h"


#ifndef ArgumentT3H2_H
#define ArgumentT3H2_H

class ArgumentT3H2 : public ActionArgument {
public:
    ArgumentT3H2(int _argID, int _agentID, int _action, int _numT, int _numK);
    bool isApplicable(std::vector<double> &state);
    unique_ptr<ActionArgument> clone() const;
};


#endif