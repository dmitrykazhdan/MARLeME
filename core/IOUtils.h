#ifndef IOUtils_H
#define IOUtils_H

#include <vector>
#include <string>
#include <memory>
#include <set>
#include "ActionArgument.h"

using namespace std;

/*
Class storing generic functionality for saving/loading data.
*/

class IOUtils {

public:
    static void saveValues(string &output_filepath, vector<double> &values);
    static void loadValues(string &file_path, vector<double> &values);
    static void saveActionArguments(string &output_filepath, set<int> &argIDs);
    static void readActionArguments(string &input_filepath, set<int> &argIDs);
};


#endif