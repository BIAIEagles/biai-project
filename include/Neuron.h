#pragma once

#include <vector>

class Neuron {
   private:
    std::vector<double> weights;
    unsigned long winnerCount;

   public:
    Neuron(std::vector<double> weights) {
        this->weights = weights;
        this->winnerCount = 0;
    }
    double calculateValue(std::vector<double> input);
    void weightsEvaluation(std::vector<double> input, double step);
    std::vector<double> getWeights();
    unsigned long getWinnerCount();
};