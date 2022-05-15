#pragma once

#include <vector>

#include "Pixel.h"

namespace SOM {
class Subframe {
   private:
    std::vector<Pixel> pixelArray;
    uint8_t lumaValue;
    uint8_t redChromaValue;
    uint8_t blueChromaValue;

   public:
    Subframe();
    Subframe(std::vector<Pixel> pixelArray);
    void setPixelArray(std::vector<Pixel> pixelArray);
    std::vector<Pixel> getPixelArray();
    void setLumaValue(uint8_t lumaValue);
    uint8_t getLumaValue();
    void setRedChromaValue(uint8_t redChromaValue);
    uint8_t getRedChromaValue();
    void setBlueChromaValue(uint8_t blueChromaValue);
    uint8_t getBlueChromaValue();
};
}  // namespace SOM