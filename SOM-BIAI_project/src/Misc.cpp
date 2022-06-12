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
    //255*255*255

    for (int i = 0; i < 255; i++) {
        for (int j = 0; j < 255; j++) {
            for (int k = 0; k < 255; k++) {
                SOM::Pixel tempPixel;
                tempPixel.setBrightness(i);
                tempPixel.setRedChroma(j);
                tempPixel.setBlueChroma(k);
                pixelArray.push_back(tempPixel);
            }
        }
    }
    std::vector<std::vector<SOM::Subframe>> frames2D =
        convertPixelArrayToSubframes(pixelArray, 4096, 4096, 4, 4);
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
        std::vector<SOM::Subframe> placeholder;
        subframes.push_back(placeholder);
        for (int j = 0; j < dimY; j+=frameDimY) {
            subframes[positionX].push_back(generateSubframe(
                pixelArray, dimX, dimY, frameDimX, frameDimY, i, j));
            positionY++;
        }
        positionX++;
    }
     return subframes;
}

SOM::Subframe generateSubframe(std::vector<SOM::Pixel> pixelArray, int dimX,
                               int dimY, int frameDimX, int frameDimY,                                 
                               int startPosX, int startPosY) {
    std::vector<SOM::Pixel> pixelSubArray;
    int subArrayIndex = 0;
    for (int i = startPosX; i < startPosX + frameDimX; i++) {
        for (int j = startPosY; j < startPosY + frameDimY;
             j++, subArrayIndex++) {
            pixelSubArray.push_back(pixelArray[i * (dimY) + j]);
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
    double normLuma = (double) euclideanNorm(lumaParts);
    double normRedChroma = (double)euclideanNorm(redChromaParts);
    double normBlueChroma = (double)euclideanNorm(blueChromaParts);
    std::vector<double> normLumaParts = normalizeVector(lumaParts);
    std::vector<double> normRedChromaParts = normalizeVector(redChromaParts);
    std::vector<double> normBlueChromaParts = normalizeVector(blueChromaParts);
    std::vector<SOM::Pixel> normPixelSubArray;
    for (int i = 0; i < frameDimX * frameDimY; i++) {
        SOM::Pixel tmp;
        tmp.setBrightness(normLumaParts[i]);
        tmp.setRedChroma(normRedChromaParts[i]);
        tmp.setBlueChroma(normBlueChromaParts[i]);
        normPixelSubArray.push_back(tmp);
    }
    SOM::Subframe result = SOM::Subframe(normPixelSubArray, normLuma, normRedChroma,
                         normBlueChroma);
    return result;
}
 std::vector<double> normalizeVector(std::vector<int> vector) {
    std::vector<double> resultVector;
    double norm = euclideanNorm(vector);
    if (norm == 0) {
        norm = 1;
    }
    for (auto item : vector) {
        resultVector.push_back(item / norm);
    }
    return resultVector;
}

 double euclideanNorm(std::vector<int> input) {
    int sum = 0;
    for (auto item : input) {
        sum += pow(item, 2);
    }
    return sqrt(sum * 1.0);
}

 std::vector<double> normalizeVector(std::vector<double> vector) {
    std::vector<double> resultVector;
    double norm = euclideanNorm(vector);
    if (norm == 0) {
        norm = 1;
    }
    for (auto item : vector) {
        resultVector.push_back(item / norm);
    }
    return resultVector;
}

double euclideanNorm(std::vector<double> input) {
    double sum = 0;
    for (auto item : input) {
        sum += pow(item, 2);
    }
    return sqrt(sum * 1.0);
}