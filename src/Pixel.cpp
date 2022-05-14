#include "../include/Pixel.h"

SOM::Pixel::Pixel(uint8_t brightness, uint8_t blue_chroma, uint8_t red_chroma) {
    this->brightness = brightness;
    this->blue_chroma = blue_chroma;
    this->red_chroma = red_chroma;
}

SOM::Pixel::Pixel() {
    this->brightness = 0;
    this->blue_chroma = 0;
    this->red_chroma = 0;
}

void SOM::Pixel::setBrightness(uint8_t brightness) {
    this->brightness = brightness;
}

uint8_t SOM::Pixel::getBrightness() { return this->brightness; }

void SOM::Pixel::setBlueChroma(uint8_t blue_chroma) {
    this->blue_chroma = blue_chroma;
}

uint8_t SOM::Pixel::getBlueChroma() { return this->blue_chroma; }

void SOM::Pixel::setRedChroma(uint8_t red_chroma) {
    this->red_chroma = red_chroma;
}