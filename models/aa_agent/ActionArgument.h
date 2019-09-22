#ifndef ActionArgument_H
#define ActionArgument_H

#include <vector>
#include <memory>
#include "Argument.h"

using namespace std;

/*
Action Argument class.

Assumes the Argument consists of a premise and a conclusion 
(effectively being an IF-THEN rule). 
If the argument is applicable in a given state (the premise is true), 
then a certain action is recommended by the conclusion.
*/

class ActionArgument : public Argument  {
public:
    ActionArgument(int _argID, int _agentID, int _action, int _numT, int _numK);
    int getConclusion();
    int getAgentID();
    int getArgID();
    void setAgentID(int _agentID);
    virtual bool isApplicable(vector<double> &state) = 0;
    virtual unique_ptr<ActionArgument> clone() const = 0;

protected:
    int numTakers;
    int numKeepers;
    int action;
    int agentID;
    int argID;
};

#endif
