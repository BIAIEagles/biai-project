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

    std::random_device device;
    std::mt19937_64 engine(device());
    std::uniform_int_distribution<> dist(0, 255);
    std::vector<SOM::Pixel> pixelArray;
    for (int j = 0; j < 16*1024; j++) {
        SOM::Pixel tempPixel;
        tempPixel.setBrightness((uint8_t)dist(engine));
        tempPixel.setRedChroma((uint8_t)dist(engine));
        tempPixel.setBlueChroma((uint8_t)dist(engine));
    }
    std::vector<std::vector<SOM::Subframe>> frames2D = convertPixelArrayToSubframes(pixelArray, 4 * 1024, 4 * 1024, 4, 4);
    for (int i = 0; i < frames2D.size(); i++) {
        for (int j = 0; j < frames2D[i].size(); j++) {
            result.push_back(frames2D[i][j]);
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

