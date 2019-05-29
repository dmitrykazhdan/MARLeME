#include "OrderingComputation.h"
#include <set>
#include <stdexcept>

using namespace std;


bool OrderingComputation::extractOrdering(ArgPreferenceGraph &preference_graph, 
                        Ordering &default_ordering,
                        Ordering &ordering ) {

    map<int, set<int>> incomingEdges;
    map<int, set<int>> outgoingEdges;

    // Apply the pruning optimisation to the preference graph.
    preference_graph.constructPreferenceGraph(incomingEdges, outgoingEdges);

    // Topologically sort the graph to extract ordering.
    return getArgumentOrderingFromPreferenceGraph(incomingEdges, outgoingEdges, default_ordering, ordering);
}


// Topologically sorts a given graph, using a variation of Kahn's algorithm.
bool OrderingComputation::getArgumentOrderingFromPreferenceGraph(
    map<int, set<int>> &incomingEdges,
    map<int, set<int>> &outgoingEdges,
    Ordering &default_ordering,
    Ordering &ordering) {

    int n_args = incomingEdges.size();
    set<int> freeNodes;

    // Create set of initial free nodes
    for (auto keyValue : incomingEdges) {
        if (incomingEdges[keyValue.first].size() == 0) {
            freeNodes.insert(keyValue.first);
        }
    }

    int nextNode = 0;
    int numRemaining = n_args;

    // Attept to extract ordering
    while (freeNodes.size() != 0 ) {

        nextNode = selectNextNode(freeNodes, default_ordering);
        freeNodes.erase(nextNode);
        ordering.setValue({nextNode, numRemaining});
        numRemaining--;

        for (auto dstNode : outgoingEdges[nextNode]) {
            
            incomingEdges[dstNode].erase(nextNode);

            if (incomingEdges[dstNode].size() == 0) {
                freeNodes.insert(dstNode);
            }
        }
    }

    // Verify whether all nodes have been extracted
    if (numRemaining > 0) {
        throw runtime_error(string("Input graph contains cycles..."));
    } else {
        return true;
    }
}



// Extract next free node (note, potentially may have multiple candidates)
int OrderingComputation::selectNextNode(set<int> &freeNodes, Ordering &ordering) {

    int maxVal = -1;
    int maxIndex = -1;

    // Next free node is extracted using the provided default ordering of nodes.
    for (auto argID : freeNodes) {
        if (ordering.getValue(argID) > maxVal) {
            maxIndex = argID;
            maxVal = ordering.getValue(argID);
        }
    }
    return maxIndex;
}