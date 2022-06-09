#pragma once
#include <stdint.h>

namespace SOM {
class Pixel {
   private:
    int brightness;
    int blue_chroma;
    int red_chroma;

   public:
    Pixel(int brightness, int blue_chroma, int red_chroma);

    Pixel();

    void setBrightness(int brightness);

    int getBrightness();

    void setBlueChroma(int blue_chroma);

    int getBlueChroma();

    void setRedChroma(int red_chroma);

    int getRedChroma();
};
}  // namespace SOM