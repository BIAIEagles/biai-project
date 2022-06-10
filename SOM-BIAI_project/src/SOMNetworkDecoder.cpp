#include "../include/SOMNetworkDecoder.h"

using namespace SOM;

SOM::SOMNetworkDecoder::SOMNetworkDecoder(
    SOMNetwork network, std::vector<std::vector<SubframeCompressed>> encodedFrames,
    int width, int height, int frameWidth, int frameHeight) {
    this->width = width;
    this->height = height;
    this->encodedFrames = encodedFrames;
    this->network = network;
    this->frameHeight = frameHeight;
    this->frameWidth = frameWidth;
}

std::vector<Pixel> SOMNetworkDecoder::decode() {
    std::vector<Pixel> result(width*height);
    int posX = 0, posY = 0;
    int frameX = 0, frameY = 0;
    for (int i = 0; i < height; i++) {
        posY = 0;
        frameY = 0;
        for (int j = 0; j < width; j++) {
            SubframeCompressed temp = this->encodedFrames[frameX][frameY];
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
            /* for (int k = 0; k < lumaPixels.size(); k++) {
                Pixel tempPixel = Pixel(denormalizedLumaPixels[k], denormalizedRedChromaPixels[k],
                                        denormalizedBlueChromaPixels[k]);

                result.push_back(tempPixel);
            }*/
            //int dataPixelIndex = 0;
            for (int pxPosX = posX; pxPosX < posX + frameHeight; pxPosX++) {
                int dataPixelIndex = 0;
                for (int pxPosY = posY; pxPosY < posY + frameWidth; pxPosY++) {
                    Pixel tempPixel = Pixel(denormalizedLumaPixels[dataPixelIndex],
                                            denormalizedRedChromaPixels[dataPixelIndex],
                                            denormalizedBlueChromaPixels[dataPixelIndex]);
                    result[(pxPosX * (posY + frameWidth)) + pxPosY] = tempPixel;
                    dataPixelIndex++;
                }
            }
            posY += frameWidth;
            frameY++;
        }
        frameX++;
        posX += frameHeight;
    }
    return result;
}

void SOM::SOMNetworkDecoder::recodePixels(std::vector<int> subData,
                                          colorPart colorChoice, int startPosX,
                                          int startPosY) {}
