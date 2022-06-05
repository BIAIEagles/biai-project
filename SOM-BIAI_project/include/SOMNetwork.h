#pragma once
#include "Neuron.h"
#include "Subframe.h"
namespace SOM {

    enum colorPart {luma, redChroma, blueChroma};

class SOMNetwork {
   private:
    std::vector<Neuron> neuronList;
    std::vector<Neuron> lumaNeuronList;
    std::vector<Neuron> redChromaNeuronList;
    std::vector<Neuron> blueChromaNeuronList;
    double trainingStep;
    int minWinnerCounter;

   public:
    SOMNetwork();
    SOMNetwork(int neuronsCount, int weightsCount, double step,
               int minWinnerCounter);
    void processFrame(Subframe frame);
    int findWinnerNeuron(std::vector<Pixel> pixelArray, colorPart colorChoice);
    void evaluateNeuronWeights(int neuronIndex, std::vector<Pixel> pixelArray, colorPart colorChoice);
    void purgeDeadNeurons();
    std::vector<double> getNeuronWeights(int index);
};
}  // namespace SOM