#include "../include/Neuron.h"

#include <math.h>

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

void Neuron::setWeights(std::vector<double> weights) { this->weights = weights; }