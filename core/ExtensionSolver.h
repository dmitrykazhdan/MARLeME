#include <set>
#include "Argument.h"
#include "ArgumentationFramework.h"
#include <memory>

using namespace std;

#ifndef ExtensionSolver_H
#define ExtensionSolver_H

/*
Abstract class used for computing a set of extensions (e.g. grounded extensions or preferred extensions ) from a given argumentation framework
*/
class ExtensionSolver {

public:
    virtual void solve(ArgumentationFramework af, set<set<int>> &extensions) = 0;
};


#endif