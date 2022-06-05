#include "../include/Misc.h"

std::vector<int> denormalizeVector(std::vector<double> input, double factor) {
    std::vector<int> result(input.size());
    for (int i = 0; i < input.size(); i++) {
        result[i] = (int)ceil(input[i] * factor);
    }
    return result;
}

std::vector<SOM::Subframe> generateRandomSubframes() {
    std::vector<SOM::Subframe> result;
    for (int i = 0; i < 255; i++) {
        for (int j = 0; j < 255; j++) {
            for (int k = 0; k < 255; k++) {
                SOM::Subframe temp;
                temp.setBlueChromaValue(i);
                temp.setRedChromaValue(j);
                temp.setLumaValue(k);
                result.push_back(temp);
            }
        }
    }
    return result;
}