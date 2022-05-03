#pragma once
#include <stdint.h>

class Pixel {
   private:
    uint8_t brightness;
    uint8_t blue_chroma;
    uint8_t red_chroma;

   public:
    Pixel(uint8_t brightness, uint8_t blue_chroma, uint8_t red_chroma);

    Pixel();

    void setBrightness(uint8_t brightness);

    uint8_t getBrightness();

    void setBlueChroma(uint8_t blue_chroma);

    uint8_t getBlueChroma();

    void setRedChroma(uint8_t red_chroma);
};