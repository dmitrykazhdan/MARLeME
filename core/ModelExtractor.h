#ifndef ModelExtractor_H
#define ModelExtractor_H

#include <vector>
#include <memory>
#include "TrajectoryData.h"
#include "StateProcessor.h"
#include "TeamModel.h"

using namespace std;

/*
Abstract class capturing model extraction behaviour.
This class takes trajectory data as input, and returns an extracted model as output.
*/

class ModelExtractor {
    virtual TeamModel* extractModel(TrajectoryData &trajectories) = 0;
};

#endif
