#ifndef OrderingComputation_H
#define OrderingComputation_H

#include "ArgPreferenceGraph.h"
#include "Ordering.h"

/*
This class extracts an argument ordering from a preference graph,
using topological sorting and a provided default node ordering.
*/

class OrderingComputation {

public:
    static bool extractOrdering(ArgPreferenceGraph &preference_graph, 
                        Ordering &default_ordering,
                        Ordering &ordering );

private:

    static bool getArgumentOrderingFromPreferenceGraph(
                map<int, set<int>> &incomingEdges,
                map<int, set<int>> &outgoingEdges,
                Ordering &default_ordering,
                Ordering &ordering);

    static int selectNextNode(set<int> &freeNodes, Ordering &ordering);

};

#endif