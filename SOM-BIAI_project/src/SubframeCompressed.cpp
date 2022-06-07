#include "../include/SubframeCompressed.h"
using namespace SOM;
SubframeCompressed::SubframeCompressed() {}
SubframeCompressed::SubframeCompressed(
    int lumaWinnerIndex, int redChromaWinnerIndex,
                   int blueChromaWinnerIndex, double lumaValue, double redChromaValue, double blueChromaValue) {
    this->lumaValue = lumaValue;
    this->redChromaValue = redChromaValue;
    this->blueChromaValue = blueChromaValue;
    this->lumaWinnerIndex = lumaWinnerIndex;
    this->redChromaWinnerIndex = redChromaWinnerIndex;
    this->blueChromaWinnerIndex = blueChromaWinnerIndex;
}
void SubframeCompressed::setLumaValue(double lumaValue) {
    this->lumaValue = lumaValue;
}
double SubframeCompressed::getLumaValue() { return this->lumaValue; }
void SubframeCompressed::setRedChromaValue(double redChromaValue) {
    this->redChromaValue = redChromaValue;
}
double SubframeCompressed::getRedChromaValue() { return this->redChromaValue; }
void SubframeCompressed::setBlueChromaValue(double blueChromaValue) {
    this->blueChromaValue = blueChromaValue;
}
double SubframeCompressed::getBlueChromaValue() {
    return this->blueChromaValue;
}
void SubframeCompressed::setLumaWinnerIndex(double lumaWinnerIndex) {
    this->lumaWinnerIndex = lumaWinnerIndex;
}
double SubframeCompressed::getLumaWinnerIndex() {
    return this->lumaWinnerIndex;
}
void SubframeCompressed::setRedChromaWinnerIndex(double redChromaWinnerIndex) {
    this->redChromaWinnerIndex = redChromaWinnerIndex;
}
double SubframeCompressed::getRedChromaWinnerIndex() {
    return this->redChromaWinnerIndex;
}
void SubframeCompressed::setBlueChromaWinnerIndex(
    double blueChromaWinnerIndex) {
    this->blueChromaWinnerIndex = blueChromaWinnerIndex;
}
double SubframeCompressed::getBlueChromaWinnerIndex() {
    return this->blueChromaWinnerIndex;
}