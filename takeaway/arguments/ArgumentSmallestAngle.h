#include "ActionArgument.h"

#ifndef ArgumentSmallestAngle_H
#define ArgumentSmallestAngle_H

class ArgumentSmallestAngle : public ActionArgument {
public:
    ArgumentSmallestAngle(int _argID, int _agentID, int _action, int _numT, int _numK);
    bool isApplicable(vector<double> &state);
    unique_ptr<ActionArgument> clone() const;
private:

};

#endif

