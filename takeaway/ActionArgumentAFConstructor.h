#ifndef ActionArgumentAFConstructor_H
#define ActionArgumentAFConstructor_H

#include <vector>
#include <memory>
#include "ArgumentationFramework.h"
#include "ActionArgument.h"

using namespace std;

/*

Argumentation Framework Constructor used for the Takeaway task.
This class injects an attack between two action arguments iff:
  1) They recommend the same action to different agents
  2) Or they recommend different actions to the same agent

*/

class ActionArgumentAFConstructor {

public:
  static void constructAF(set<int> &argIDs, const vector<unique_ptr<ActionArgument>> &actionArgsTable, ArgumentationFramework &af);

};

#endif