#include "../include/Subframe.h"

using namespace SOM;

Subframe::Subframe() {}
Subframe::Subframe(std::vector<Pixel> pixelArray) {
    this->pixelArray = pixelArray;
}

SOM::Subframe::Subframe(std::vector<Pixel> pixelArray, double luma,
                        double redChroma, double blueChroma) {
    this->pixelArray = pixelArray;
    this->lumaValue = luma;
    this->redChromaValue = redChroma;
    this->blueChromaValue = blueChroma;
}

void Subframe::setPixelArray(std::vector<Pixel> pixelArray) {
    this->pixelArray = pixelArray;
}
std::vector<Pixel> Subframe::getPixelArray() { return this->pixelArray; }
void Subframe::setLumaValue(double lumaValue) { this->lumaValue = lumaValue; }
double Subframe::getLumaValue() { return this->lumaValue; }
void Subframe::setRedChromaValue(double redChromaValue) {
    this->redChromaValue = redChromaValue;
}
double Subframe::getRedChromaValue() { return this->redChromaValue; }
void Subframe::setBlueChromaValue(double blueChromaValue) {
    this->blueChromaValue = blueChromaValue;
}
double Subframe::getBlueChromaValue() { return this->blueChromaValue; }

int SOM::Subframe::getWidth() { return this->width; }

void SOM::Subframe::setWidth(int width) { this->width = width; }

int SOM::Subframe::getHeight() { return this->height; }

void SOM::Subframe::setHeight(int height) { this->height = height; }
