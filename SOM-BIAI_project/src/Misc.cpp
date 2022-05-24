#include "../include/Misc.h"

std::vector<int> denormalizeVector(std::vector<double> input, double factor) {
    std::vector<int> result;
    for (auto item : input) {
        result.push_back((int)round(item * factor));
    }
    return result;
}

SOM::Subframe generateRandomSubframe(int x_dim, int y_dim) { 
    SOM::Subframe subframe();
    return subframe();
}