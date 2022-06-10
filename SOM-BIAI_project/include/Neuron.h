#pragma once

#include <vector>
#include "Misc.h"
namespace SOM {
class Neuron {
   private:
    std::vector<double> weights;
    unsigned long winnerCount;

   public:
    Neuron(std::vector<double> weights);
    double calculateValue(std::vector<double> input);
    void weightsEvaluation(std::vector<double> input, double step);
    std::vector<double> getWeights();
    unsigned long getWinnerCount();
    void setWeights(std::vector<double> weights);
};
}