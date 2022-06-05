#pragma once

#include <vector>

#include "Pixel.h"

namespace SOM {
class Subframe {
   private:
    std::vector<Pixel> pixelArray;
    double lumaValue;
    double redChromaValue;
    double blueChromaValue;
    int width;
    int height;

   public:
    Subframe();
    Subframe(std::vector<Pixel> pixelArray);
    Subframe(std::vector<Pixel> pixelArray, double luma, double redChroma, double blueChroma);
    void setPixelArray(std::vector<Pixel> pixelArray);
    std::vector<Pixel> getPixelArray();
    void setLumaValue(double lumaValue);
    double getLumaValue();
    void setRedChromaValue(double redChromaValue);
    double getRedChromaValue();
    void setBlueChromaValue(double blueChromaValue);
    double getBlueChromaValue();
    int getWidth();
    void setWidth(int width);
    int getHeight();
    void setHeight(int height);
};
}  // namespace SOM