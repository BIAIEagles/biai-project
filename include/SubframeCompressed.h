#pragma once

#include <vector>

#include "Pixel.h"

namespace SOM {
class SubframeCompressed {
   private:
    int lumaWinnerIndex;
    int redChromaWinnerIndex;
    int blueChromaWinnerIndex;
    uint8_t lumaValue;
    uint8_t redChromaValue;
    uint8_t blueChromaValue;

   public:
    SubframeCompressed();
    SubframeCompressed(int lumaWinnerIndex, int redChromaWinnerIndex,
                       int blueChromaWinnerIndex, uint8_t lumaValue,
                       uint8_t redChromaValue, uint8_t blueChromaValue);
    void setLumaValue(uint8_t lumaValue);
    uint8_t getLumaValue();
    void setRedChromaValue(uint8_t redChromaValue);
    uint8_t getRedChromaValue();
    void setBlueChromaValue(uint8_t blueChromaValue);
    uint8_t getBlueChromaValue();
    void setLumaWinnerIndex(uint8_t lumaWinnerIndex);
    uint8_t getLumaWinnerIndex();
    void setRedChromaWinnerIndex(uint8_t redChromaWinnerIndex);
    uint8_t getRedChromaWinnerIndex();
    void setBlueChromaWinnerIndex(uint8_t blueChromaWinnerIndex);
    uint8_t getBlueChromaWinnerIndex();
};
}  // namespace SOM