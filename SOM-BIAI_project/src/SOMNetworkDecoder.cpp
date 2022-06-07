#include "../include/SOMNetworkDecoder.h"

using namespace SOM;

SOM::SOMNetworkDecoder::SOMNetworkDecoder(
    SOMNetwork network, std::vector<SubframeCompressed> encodedFrames,
    int width, int height) {
    this->width = width;
    this->height = height;
    this->encodedFrames = encodedFrames;
    this->network = network;
}

std::vector<Pixel> SOMNetworkDecoder::decode() {
    std::vector<Pixel> result;
    int posX = 0, posY = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            SubframeCompressed temp = this->encodedFrames[i * width + j];
            int lumaWinnerNeuronIndex = temp.getLumaWinnerIndex();
            int redChromaWinnerIndex = temp.getRedChromaWinnerIndex();
            int blueChromaWinnerIndex = temp.getBlueChromaWinnerIndex();
            std::vector<double> lumaPixels =
                this->network.getNeuronWeights(lumaWinnerNeuronIndex);
            std::vector<double> redChromaPixels =
                this->network.getRedChromaNeuronWeights(redChromaWinnerIndex);
            std::vector<double> blueChromaPixels =
                this->network.getBlueChromaNeuronWeights(blueChromaWinnerIndex);
            std::vector<int> denormalizedLumaPixels =
                denormalizeVector(lumaPixels, temp.getLumaValue());
            std::vector<int> denormalizedRedChromaPixels =
                denormalizeVector(redChromaPixels, temp.getRedChromaValue());
            std::vector<int> denormalizedBlueChromaPixels =
                denormalizeVector(blueChromaPixels, temp.getBlueChromaValue());
            for (int k = 0; k < lumaPixels.size(); k++) {
                Pixel tempPixel = Pixel(lumaPixels[k], redChromaPixels[k],
                                        blueChromaPixels[k]);
                result.push_back(tempPixel);
            }
        }
    }
    return result;
}

void SOM::SOMNetworkDecoder::recodePixels(std::vector<int> subData,
                                          colorPart colorChoice, int startPosX,
                                          int startPosY) {}
