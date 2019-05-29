#include "ActionArgument.h"


#ifndef ArgumentFarKeeper_H
#define ArgumentFarKeeper_H


class ArgumentFarKeeper : public ActionArgument {
public:
    ArgumentFarKeeper(int _argID, int _agentID, int _action, int _numT, int _numK);
    bool isApplicable(vector<double> &state);
    unique_ptr<ActionArgument> clone() const;
private:

};

#endif

