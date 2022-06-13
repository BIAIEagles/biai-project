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
               int minWinnerCounter, std::vector<Pixel> randomPixels);
    void processFrame(Subframe frame);
    int findWinnerNeuron(std::vector<Pixel> pixelArray, colorPart colorChoice);
    void evaluateNeuronWeights(int neuronIndex, std::vector<Pixel> pixelArray, colorPart colorChoice);
    void purgeDeadNeurons();
    std::vector<double> getNeuronWeights(int index);
    std::vector<double> getLumaNeuronWeights(int index);
    std::vector<double> getRedChromaNeuronWeights(int index);
    std::vector<double> getBlueChromaNeuronWeights(int index);

    std::vector<Neuron> getLumaNeurons();
    std::vector<Neuron> getRedChromaNeurons();
    std::vector<Neuron> getBlueChromaNeurons();
    void setLumaNeurons(std::vector<Neuron> neuronList);
    void setRedChromaNeurons(std::vector<Neuron> neuronList);
    void setBlueChromaNeurons(std::vector<Neuron> neuronList);
};
}  // namespace SOM