#include "ActionArgument.h"


#ifndef ArgumentT2H1_H
#define ArgumentT2H1_H

class ArgumentT2H1 : public ActionArgument {
public:
    ArgumentT2H1(int _argID, int _agentID, int _action, int _numT, int _numK);
    bool isApplicable(std::vector<double> &state);
    unique_ptr<ActionArgument> clone() const;
};


#endif