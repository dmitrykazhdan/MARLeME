#ifndef TeamModel_H
#define TeamModel_H

#include <string>
#include <vector>

using namespace std;

/*
Abstract class representing a team model, which may contain other team or agent models.
This class processes a set of states, and returns a set of states as output.
*/

class TeamModel {
  void processStates(vector<vector<double>> &states, vector<vector<double>> &outputs);
};

#endif
