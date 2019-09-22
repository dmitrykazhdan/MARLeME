#include "ActionArgument.h"

#ifndef ArgumentOpenKeeper_H
#define ArgumentOpenKeeper_H

class ArgumentOpenKeeper : public ActionArgument {
public:
    ArgumentOpenKeeper(int _argID, int _agentID, int _action, int _numT, int _numK);
    bool isApplicable(vector<double> &state);
    unique_ptr<ActionArgument> clone() const;
private:

};

#endif


