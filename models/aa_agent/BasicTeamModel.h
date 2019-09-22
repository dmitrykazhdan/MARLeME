#ifndef BasicTeamModel_H
#define BasicTeamModel_H

#include <vector>
#include <memory>
#include "TeamModel.h"
#include "AFAgentModel.h"

using namespace std;

/*

This class is a simple container for several AFAgentModel objects.
Input states are simply passed to their respective agents, and the outputs are concatenated.
No extra coordination/team processing is performed.
*/

class BasicTeamModel : public TeamModel {

public:
    void addAgent(unique_ptr<AFAgentModel> agent);
    void processStates(vector<vector<double>> &states, vector<vector<double>> &outputs);
    void saveAgentOrderings(vector<string> &outputPaths);
private:
    vector<unique_ptr<AFAgentModel>> agents;
};


#endif
