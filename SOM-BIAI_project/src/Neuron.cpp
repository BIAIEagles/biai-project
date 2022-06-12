#include "../include/Neuron.h"

#include <math.h>
#include <string>

#include <algorithm>
using namespace SOM;

Neuron::Neuron(std::vector<double> weights) {
    this->weights = weights;
    this->winnerCount = 0;
}

double Neuron::calculateValue(std::vector<double> input) {
    double sum = 0;
    for (int i = 0; i < input.size(); i++) {
        sum += pow(input[i] - this->weights[i], 2);
    }
    return sqrt(sum);  // normalized output
}

void Neuron::weightsEvaluation(std::vector<double> input, double step) {
    this->winnerCount++;
    for (int i = 0; i < weights.size(); i++) {
        weights[i] += step * (input[i] - weights[i]);
    }

    this->weights = normalizeVector(weights);
}

std::vector<double> Neuron::getWeights() { return this->weights; }

unsigned long Neuron::getWinnerCount() { return this->winnerCount; }

void SOM::Neuron::setWinnerCount(unsigned long winnerCount) {
    this->winnerCount = winnerCount;
}

void Neuron::setWeights(std::vector<double> weights) {
    this->weights = weights;
}

std::string SOM::Neuron::serialize() {
    std::string result;
    result += std::to_string(this->winnerCount);
    result += ";";
    for (auto weight : this->weights) {
        result += std::to_string(weight);
        result += ";";
    }
    //result.pop_back();
    result += "\n";
    return result;
}

bool neuronBelowThreshold(SOM::Neuron neuron) {
    return neuron.getWinnerCount() < 10 ? true : false;
}