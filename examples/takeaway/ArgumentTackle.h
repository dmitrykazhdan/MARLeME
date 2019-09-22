#include "ActionArgument.h"

#ifndef ArgumentTackle_H
#define ArgumentTackle_H

class ArgumentTackle : public ActionArgument {
public:
    ArgumentTackle(int _argID, int _agentID, int _action, int _numT, int _numK);
    bool isApplicable(std::vector<double> &state);
    unique_ptr<ActionArgument> clone() const;
};


#endif