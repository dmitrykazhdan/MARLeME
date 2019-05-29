#ifndef GESolver_H
#define GESolver_H

#include "ExtensionSolver.h"

/*
Class for computing the grounded extension of a given argumentation framework.
*/
class GESolver : public ExtensionSolver {
public:
    void solve(ArgumentationFramework af, set<set<int>> &extensions);
};

#endif