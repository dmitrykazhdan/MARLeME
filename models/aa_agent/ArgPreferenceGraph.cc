#include "ArgPreferenceGraph.h"
#include <string>
#include <stdexcept>


ArgPreferenceGraph::ArgPreferenceGraph(const ArgPreferenceGraph &oldAPG) :
allNodes(oldAPG.allNodes), edgeWeights(oldAPG.edgeWeights) {

}


ArgPreferenceGraph::ArgPreferenceGraph() :
allNodes(), edgeWeights() 
{
}

// Initialise all edge weights to 0
void ArgPreferenceGraph::initialize(set<int> &_allNodes) {

    for (auto arg : _allNodes) {
        allNodes.push_back(arg);
    }

    int arg1 = 0;
    int arg2 = 0;

    for (int i = 0; i < allNodes.size(); i++) {
        for (int j = i; j < allNodes.size(); j++) {

            arg1 = allNodes.at(i);
            arg2 = allNodes.at(j);

            edgeWeights[{arg1, arg2}] = 0;
            edgeWeights[{arg2, arg1}] = 0;
        }
    }
}

// Add 1 to the edge weight of the edge (preferred, non_preferred)
void ArgPreferenceGraph::incrementPreference(int preferred, int non_preferred) {

    if (edgeWeights.find({preferred, non_preferred}) != edgeWeights.end()) {
        edgeWeights[{preferred, non_preferred}] += 1;
    } else {
        throw runtime_error(string("Error: Nodes not found in defined graph..."));
    }
}

// Use the pruning heuristic to prune edges, and discard remaining weight information
void ArgPreferenceGraph::constructPreferenceGraph(map<int, set<int>> &incomingEdges, map<int, set<int>> &outgoingEdges) {

    int n_args = allNodes.size(); // get count of attack graph

    for (int i = 0; i < n_args; i++) {
        set<int> empty1;
        set<int> empty2;
        incomingEdges.insert({allNodes.at(i), empty1});
        outgoingEdges.insert({allNodes.at(i), empty2});
    }

    int w1 = 0;
    int w2 = 0;
    int preference = 0;
    int arg1 = 0;
    int arg2 = 0;
    int pruning_val = 100;

    for (int i = 0; i < n_args; i++) {
        for (int j = i; j < n_args; j++) {

            arg1 = allNodes.at(i);
            arg2 = allNodes.at(j);
            w1 = edgeWeights[{arg1, arg2}];
            w2 = edgeWeights[{arg2, arg1}];
            preference = w1 - w2;

            if (preference > pruning_val) {
                incomingEdges[arg2].insert(arg1);
                outgoingEdges[arg1].insert(arg2);

            } else if (preference < -pruning_val) {
                incomingEdges[arg1].insert(arg2);
                outgoingEdges[arg2].insert(arg1);
            }
        }
    }
}



