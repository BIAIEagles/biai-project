#pragma once

#include <vector>

#include "Pixel.h"

namespace SOM {
class SubframeCompressed {
   private:
    int lumaWinnerIndex;
    int redChromaWinnerIndex;
    int blueChromaWinnerIndex;
    double lumaValue;
    double redChromaValue;
    double blueChromaValue;

   public:
    SubframeCompressed();
    SubframeCompressed(int lumaWinnerIndex, int redChromaWinnerIndex,
                       int blueChromaWinnerIndex, double lumaValue,
                       double redChromaValue, double blueChromaValue);
    void setLumaValue(double lumaValue);
    double getLumaValue();
    void setRedChromaValue(double redChromaValue);
    double getRedChromaValue();
    void setBlueChromaValue(double blueChromaValue);
    double getBlueChromaValue();
    void setLumaWinnerIndex(double lumaWinnerIndex);
    double getLumaWinnerIndex();
    void setRedChromaWinnerIndex(double redChromaWinnerIndex);
    double getRedChromaWinnerIndex();
    void setBlueChromaWinnerIndex(double blueChromaWinnerIndex);
    double getBlueChromaWinnerIndex();
};
}  // namespace SOM