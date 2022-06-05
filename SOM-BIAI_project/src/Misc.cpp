#include "../include/Misc.h"

std::vector<int> denormalizeVector(std::vector<double> input, double factor) {
    std::vector<int> result(input.size());
    for (int i = 0; i < input.size(); i++) {
        result[i] = (int)ceil(input[i] * factor);
    }
    return result;
}

std::vector<SOM::Subframe> generateRandomSubframes() {
    std::vector<SOM::Subframe> result;
    for (int i = 0; i < 255; i++) {
        for (int j = 0; j < 255; j++) {
            for (int k = 0; k < 255; k++) {
                SOM::Subframe temp;
                temp.setBlueChromaValue(i);
                temp.setRedChromaValue(j);
                temp.setLumaValue(k);
                result.push_back(temp);
            }
        }
    }
    return result;
}

std::vector<std::vector<SOM::Subframe>> convertPixelArrayToSubframes(
    std::vector<SOM::Pixel> pixelArray, int dimX, int dimY, int frameDimX,
    int frameDimY) {
    std::vector<std::vector<SOM::Subframe>> subframes;
    int positionX = 0, positionY = 0;
    for (int i = 0; i < dimX; i+=frameDimX) {
        positionY = 0;
        for (int j = 0; j < dimY; j+=frameDimY) {
            subframes[positionX][positionY] = generateSubframe(
                pixelArray, dimX, dimY, frameDimX, frameDimY, i, j);
            positionY++;
        }
        positionX++;
    }
    return subframes;
}

SOM::Subframe generateSubframe(std::vector<SOM::Pixel> pixelArray, int dimX,
                               int dimY, int frameDimX, int frameDimY,
                               int startPosX, int startPosY) {
    std::vector<SOM::Pixel> pixelSubArray(frameDimX * frameDimY);
    int subArrayIndex = 0;
    for (int i = startPosX; i < startPosX + frameDimX; i++) {
        for (int j = startPosY; j < startPosY + frameDimY;
             j++, subArrayIndex++) {
            pixelSubArray[subArrayIndex] = pixelArray[i * dimX + j];
        }
    }
    std::vector<int> lumaParts(frameDimX * frameDimY);
    std::vector<int> redChromaParts(frameDimX * frameDimY);
    std::vector<int> blueChromaParts(frameDimX * frameDimY);
    for (int i = 0; i < frameDimX * frameDimY; i++) {
        lumaParts[i] = pixelSubArray[i].getBrightness();
        redChromaParts[i] = pixelSubArray[i].getRedChroma();
        blueChromaParts[i] = pixelSubArray[i].getBlueChroma();
    }
    double normLuma = (double) euclideanNorm<int>(lumaParts);
    double normRedChroma = (double)euclideanNorm<int>(redChromaParts);
    double normBlueChroma = (double)euclideanNorm<int>(blueChromaParts);
    SOM::Subframe result(pixelSubArray, normLuma, normRedChroma,
                         normBlueChroma);
    return result;
}

