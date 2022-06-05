#include "../include/Subframe.h"

using namespace SOM;

Subframe::Subframe() {}
Subframe::Subframe(std::vector<Pixel> pixelArray) {
    this->pixelArray = pixelArray;
}
void Subframe::setPixelArray(std::vector<Pixel> pixelArray) {
    this->pixelArray = pixelArray;
}
std::vector<Pixel> Subframe::getPixelArray() { return this->pixelArray; }
void Subframe::setLumaValue(uint8_t lumaValue) { this->lumaValue = lumaValue; }
uint8_t Subframe::getLumaValue() { return this->lumaValue; }
void Subframe::setRedChromaValue(uint8_t redChromaValue) {
    this->redChromaValue = redChromaValue;
}
uint8_t Subframe::getRedChromaValue() { return this->redChromaValue; }
void Subframe::setBlueChromaValue(uint8_t blueChromaValue) {
    this->blueChromaValue = blueChromaValue;
}
uint8_t Subframe::getBlueChromaValue() { return this->blueChromaValue; }