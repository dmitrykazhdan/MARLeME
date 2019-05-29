#include "BasicStateConverter.h"
#include "BasicValueExtractor.h"

BasicStateConverter::BasicStateConverter(int _keyID, BasicValueExtractor _valueExtractor)
 : keyID(_keyID), valueExtractor(_valueExtractor) {
}

void BasicStateConverter::convert(vector<vector<double>> &states, vector<double> &values) {

    // Copy specified vactor as-is
    for (int i = 0; i < states.at(keyID).size(); i++) {
        values.push_back(states.at(keyID).at(i));
    }

    // Copy subset of data from remaining vectors
    for (int i = 0; i < states.size(); i++){
        if (i == keyID) {
            continue;
        }

        vector<double> extractedVals;
        valueExtractor.convert(states.at(i), extractedVals);

        for (int j = 0; j < extractedVals.size(); j++) {
            values.push_back(extractedVals.at(j));
        }
    }
}