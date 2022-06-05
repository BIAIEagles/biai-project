#include "../include/SOMNetwork.h"

using namespace SOM;

SOMNetwork::SOMNetwork() {
    this->trainingStep = 1;
    this->minWinnerCounter = 2;
}

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

void SOMNetwork::processFrame(Subframe frame) {
    int winnerNeuronIndexLuma =
        this->findWinnerNeuron(frame.getPixelArray(), luma);
    int winnerNeuronIndexRedChroma =
        this->findWinnerNeuron(frame.getPixelArray(), redChroma);
    int winnerNeuronIndexBlueChroma =
        this->findWinnerNeuron(frame.getPixelArray(), blueChroma);
}

int SOMNetwork::findWinnerNeuron(std::vector<Pixel> pixelArray, colorPart colorChoice) {
    std::vector<double> pixelArrayPart;
    std::vector<double> neuronValues;
    switch (colorChoice) {
        case luma: {
            for (auto pixel : pixelArray) {
                pixelArrayPart.push_back(pixel.getBrightness());
            }
            for (auto neuron : this->lumaNeuronList) {
                neuronValues.push_back(neuron.calculateValue(pixelArrayPart));
                // neuron list with 255*255*255 neurons
            }
            return findMinIndex<double>(neuronValues);
            break;
        }
        case redChroma: {
            for (auto pixel : pixelArray) {
                pixelArrayPart.push_back(pixel.getRedChroma());
            }
            for (auto neuron : this->redChromaNeuronList) {
                neuronValues.push_back(neuron.calculateValue(pixelArrayPart));
                // neuron list with 255*255*255 neurons
            }
            return findMinIndex<double>(neuronValues);
            break;
        }
        case blueChroma: {
            for (auto pixel : pixelArray) {
                pixelArrayPart.push_back(pixel.getBlueChroma());
            }
            for (auto neuron : this->blueChromaNeuronList) {
                neuronValues.push_back(neuron.calculateValue(pixelArrayPart));
                // neuron list with 255*255*255 neurons
            }
            return findMinIndex<double>(neuronValues);
            break;
        }
        default:
            return -1;
    }
}

void SOMNetwork::evaluateNeuronWeights(int neuronIndex,
                                       std::vector<Pixel> pixelArray, colorPart colorChoice) {
    if (neuronIndex >= this->neuronList.size()) {
        return;
    }
    std::vector<double> pixelArrayPart;
    switch (colorChoice) {
        case luma: {
            for (auto pixel : pixelArray) {
                pixelArrayPart.push_back(pixel.getBrightness());
            }
            Neuron neuron = this->lumaNeuronList[neuronIndex];
            neuron.weightsEvaluation(pixelArrayPart, this->trainingStep);
            break;        
        }
        case redChroma: {
            for (auto pixel : pixelArray) {
                pixelArrayPart.push_back(pixel.getRedChroma());
            }
            Neuron neuron = this->redChromaNeuronList[neuronIndex];
            neuron.weightsEvaluation(pixelArrayPart, this->trainingStep);
            break;
        }
        case blueChroma: {
            for (auto pixel : pixelArray) {
                pixelArrayPart.push_back(pixel.getBlueChroma());
            }
            Neuron neuron = this->blueChromaNeuronList[neuronIndex];
            neuron.weightsEvaluation(pixelArrayPart, this->trainingStep);
            break;
        }
    }
}

void SOMNetwork::purgeDeadNeurons() {
    for (int i = 0; i < this->lumaNeuronList.size(); i++) {
        if (this->lumaNeuronList[i].getWinnerCount() < this->minWinnerCounter) {
            this->lumaNeuronList.erase(this->lumaNeuronList.begin() + i);
        }
    }
    for (int i = 0; i < this->blueChromaNeuronList.size(); i++) {
        if (this->blueChromaNeuronList[i].getWinnerCount() < this->minWinnerCounter) {
            this->blueChromaNeuronList.erase(this->blueChromaNeuronList.begin() + i);
        }
    }
    for (int i = 0; i < this->redChromaNeuronList.size(); i++) {
        if (this->redChromaNeuronList[i].getWinnerCount() < this->minWinnerCounter) {
            this->redChromaNeuronList.erase(this->redChromaNeuronList.begin() + i);
        }
    }
}

std::vector<double> SOMNetwork::getNeuronWeights(int index) {
    return this->neuronList[index].getWeights();
}