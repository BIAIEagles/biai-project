#pragma once

#include <math.h>

#include <algorithm>
#include <functional>
#include <random>
#include <vector>
#include "Subframe.h"

std::vector<double> normalizeVector(std::vector<int> vector);

std::vector<double> normalizeVector(std::vector<double> vector);

double euclideanNorm(std::vector<int> input);

double euclideanNorm(std::vector<double> input);

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
    T minVal = input[0];
    for (auto it : input) {
        if (it < minVal) {
            minVal = it;
        }
    }
    //int minVal = input.at(std::distance(input.begin(), std::min_element(input.begin(), input.end())));
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

std::vector <std::vector<SOM::Subframe>> convertPixelArrayToSubframes(
                  std::vector<SOM::Pixel> pixelArray, int dimX, int dimY, int frameDimX, int frameDimY);

SOM::Subframe generateSubframe(std::vector<SOM::Pixel> pixelArray, int dimX,
                               int dimY, int frameDimX,
                               int frameDimY, int startPosX, int startPosY);