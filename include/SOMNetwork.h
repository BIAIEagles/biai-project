#pragma once
#include "Neuron.h"
#include "Subframe.h"
namespace SOM {
class SOMNetwork {
   private:
    std::vector<Neuron> neuronList;
    double trainingStep;
    int minWinnerCounter;

   public:
    SOMNetwork(int neuronsCount, int weightsCount, double step,
               int minWinnerCounter);
    void processFrame(Subframe frame);
    int findWinnerNeuron(std::vector<double> pixelArray);
    void evaluateNeouronWeights(int neuronIndex,
                                std::vector<double> pixelArray);
    void purgeDeadNeurons();
    std::vector<double> getNeuronWeights(int index);
};
}  // namespace SOM