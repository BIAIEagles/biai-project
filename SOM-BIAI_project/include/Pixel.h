#pragma once
#include <stdint.h>

namespace SOM {
class Pixel {
   private:
    double brightness;
    double blue_chroma;
    double red_chroma;

   public:
    Pixel(double brightness, double blue_chroma, double red_chroma);

    Pixel();

    void setBrightness(double brightness);

    double getBrightness();

    void setBlueChroma(double blue_chroma);

    double getBlueChroma();

    void setRedChroma(double red_chroma);

    double getRedChroma();
};
}  // namespace SOM