#include "../include/SOMNetworkEncoder.h"

using namespace SOM;

SOMNetworkEncoder::SOMNetworkEncoder(SOMNetwork network) {
    this->network = network;
}

std::vector<std::vector<SubframeCompressed>> SOMNetworkEncoder::encode(
    std::vector<std::vector<Subframe>> frames) {
    std::vector<std::vector<SubframeCompressed>> encodedFrames;
    for (int i = 0; i < frames.size(); i++) {
        std::vector<SubframeCompressed> tempVec(frames[i].size());
        encodedFrames.push_back(tempVec);
        for (int j = 0; j < frames[i].size(); j++) {
            int winnerNeuronIndexLuma =
                network.findWinnerNeuron(frames[i][j].getPixelArray(), luma);
            int winnerNeuronIndexRedChroma = network.findWinnerNeuron(
                frames[i][j].getPixelArray(), redChroma);
            int winnerNeuronIndexBlueChroma = network.findWinnerNeuron(
                frames[i][j].getPixelArray(), blueChroma);
            SubframeCompressed temp(
                winnerNeuronIndexLuma, winnerNeuronIndexRedChroma,
                winnerNeuronIndexBlueChroma, frames[i][j].getLumaValue(),
                frames[i][j].getRedChromaValue(),
                frames[i][j].getBlueChromaValue());
            encodedFrames[i][j] = temp;
        }
    }
      return encodedFrames;
}