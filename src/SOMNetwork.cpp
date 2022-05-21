#include "../include/SOMNetwork.h"

#include "../include/Misc.h"

using namespace SOM;

SOMNetwork::SOMNetwork(int neuronsCount, int weightsCount, double step,
                       int minWinnerCounter) {
    this->trainingStep = step;
    this->minWinnerCounter = minWinnerCounter;

    for (int i = 0; i < neuronsCount; i++) {
        std::vector<double> weights =
            normalizeVector<double>(generateWeights<double>(weightsCount));
        Neuron neuron(weights);
        this->neuronList.push_back(neuron);
    }
}

void SOMNetwork::processFrame(Subframe frame) {}

int SOMNetwork::findWinnerNeuron(std::vector<double> pixelArray) {
    std::vector<double> neuronValues;
    for (auto neuron : this->neuronList) {
        neuronValues.push_back(neuron.calculateValue(pixelArray));
    }
    return findMinIndex(neuronValues);
}

void SOMNetwork::evaluateNeuronWeights(int neuronIndex,
                                       std::vector<double> pixelArray) {
    if (neuronIndex >= this->neuronList.size()) {
        return;
    }
    Neuron neuron = this->neuronList[neuronIndex];
    neuron.weightsEvaluation(pixelArray, this->trainingStep);
}

void SOMNetwork::purgeDeadNeurons() {
    for (int i = 0; i < this->neuronList.size(); i++) {
        if (this->neuronList[i].getWinnerCount() < this->minWinnerCounter) {
            this->neuronList.erase(this->neuronList.begin() + i);
        }
    }
}

std::vector<double> SOMNetwork::getNeuronWeights(int index) {
    return this->neuronList[index].getWeights();
}