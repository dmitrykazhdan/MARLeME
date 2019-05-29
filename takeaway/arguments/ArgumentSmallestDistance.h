#include "ActionArgument.h"

#ifndef ArgumentSmallestDistance_H
#define ArgumentSmallestDistance_H

class ArgumentSmallestDistance : public ActionArgument  {
public:
    ArgumentSmallestDistance(int _argID, int _agentID, int _action, int _numT, int _numK);
    bool isApplicable(vector<double> &state);
    unique_ptr<ActionArgument> clone() const;
private:

};

#endif

