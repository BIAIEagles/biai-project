#include "../include/SubframeCompressed.h"
using namespace SOM;
SubframeCompressed::SubframeCompressed() {}
SubframeCompressed::SubframeCompressed(
    int lumaWinnerIndex, int redChromaWinnerIndex,
                   int blueChromaWinnerIndex, uint8_t lumaValue, uint8_t redChromaValue, uint8_t blueChromaValue) {
    this->lumaValue = lumaValue;
    this->redChromaValue = redChromaValue;
    this->blueChromaValue = blueChromaValue;
    this->lumaWinnerIndex = lumaWinnerIndex;
    this->redChromaWinnerIndex = redChromaWinnerIndex;
    this->blueChromaWinnerIndex = blueChromaWinnerIndex;
}
void SubframeCompressed::setLumaValue(uint8_t lumaValue) {
    this->lumaValue = lumaValue;
}
uint8_t SubframeCompressed::getLumaValue() { return this->lumaValue; }
void SubframeCompressed::setRedChromaValue(uint8_t redChromaValue) {
    this->redChromaValue = redChromaValue;
}
uint8_t SubframeCompressed::getRedChromaValue() { return this->redChromaValue; }
void SubframeCompressed::setBlueChromaValue(uint8_t blueChromaValue) {
    this->blueChromaValue = blueChromaValue;
}
uint8_t SubframeCompressed::getBlueChromaValue() {
    return this->blueChromaValue;
}
void SubframeCompressed::setLumaWinnerIndex(uint8_t lumaWinnerIndex) {
    this->lumaWinnerIndex = lumaWinnerIndex;
}
uint8_t SubframeCompressed::getLumaWinnerIndex() {
    return this->lumaWinnerIndex;
}
void SubframeCompressed::setRedChromaWinnerIndex(uint8_t redChromaWinnerIndex) {
    this->redChromaWinnerIndex = redChromaWinnerIndex;
}
uint8_t SubframeCompressed::getRedChromaWinnerIndex() {
    return this->redChromaWinnerIndex;
}
void SubframeCompressed::setBlueChromaWinnerIndex(
    uint8_t blueChromaWinnerIndex) {
    this->blueChromaWinnerIndex = blueChromaWinnerIndex;
}
uint8_t SubframeCompressed::getBlueChromaWinnerIndex() {
    return this->blueChromaWinnerIndex;
}