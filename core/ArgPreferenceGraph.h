#ifndef ArgPreferenceGraph_H
#define ArgPreferenceGraph_H

#include <vector>
#include <map>
#include <set>
#include "Argument.h"


using namespace std;

/*
The Argument Preference Graph stores pairwise preferences between arguments.
It is a directed weighted graph with non-negative weights, where nodes represent
arguments, and edges represent preferences between arguments.

Thus, a directed edge from argument A to argument B of weight w indicates that A is 
preferred to B, with the semantics of w being task-dependent.
*/

class ArgPreferenceGraph {

public:
    ArgPreferenceGraph();
    ArgPreferenceGraph (const ArgPreferenceGraph &oldAPG);
    void initialize(set<int> &_allNodes);
    void incrementPreference(int preferred, int non_preferred);
    void constructPreferenceGraph(map<int, set<int>> &incomingEdges, map<int, set<int>> &outgoingEdges);
    
private:
    vector<int> allNodes;
    map<pair<int, int>, int> edgeWeights;
};

#endif