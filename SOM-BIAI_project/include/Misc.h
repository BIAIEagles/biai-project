#pragma once

#include <math.h>

#include <algorithm>
#include <functional>
#include <random>
#include <vector>
#include "Subframe.h"

template <class T>
std::vector<T> normalizeVector(std::vector<T> vector) {
    std::vector<T> resultVector;
    double norm = euclideanNorm<T>(vector);
    for (auto item : vector) {
        resultVector.push_back(item / norm);
    }
    return vector;
}

template <class T>
static T euclideanNorm(std::vector<T> input) {
    T sum = 0;
    for (auto item : input) {
        sum += pow(item, 2);
    }
    return sqrt(sum);
}

template <class T>
std::vector<T> generateWeights(int count) {
    std::vector<T> weights;
    std::random_device device;
    std::mt19937_64 engine(device());
    std::uniform_int_distribution<> dist(0, 255);

    for (int i = 0; i < count; i++) {
        weights.push_back(dist(engine));
    }
    return weights;
}

template <class T>
int findMinIndex(std::vector<T> input) {
    int minVal = input.at(std::distance(input.begin(), std::min_element(input.begin(), input.end())));
    int index = 0;
    for (int i = 0; i < input.size(); i++) {
        if (minVal == input[i]) {
            index = i;
            break;
        }
    }
    return index;
}

std::vector<int> denormalizeVector(std::vector<double> input, double factor);

std::vector<SOM::Subframe> generateRandomSubframes();