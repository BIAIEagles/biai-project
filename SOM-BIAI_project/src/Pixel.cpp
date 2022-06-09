#include "../include/Pixel.h"

SOM::Pixel::Pixel(int brightness, int blue_chroma, int red_chroma) {
    this->brightness = brightness;
    this->blue_chroma = blue_chroma;
    this->red_chroma = red_chroma;
}

SOM::Pixel::Pixel() {
    this->brightness = 0;
    this->blue_chroma = 0;
    this->red_chroma = 0;
}

void SOM::Pixel::setBrightness(int brightness) {
    this->brightness = brightness;
}

int SOM::Pixel::getBrightness() { return this->brightness; }

void SOM::Pixel::setBlueChroma(int blue_chroma) {
    this->blue_chroma = blue_chroma;
}

int SOM::Pixel::getBlueChroma() { return this->blue_chroma; }

void SOM::Pixel::setRedChroma(int red_chroma) {
    this->red_chroma = red_chroma;
}

int SOM::Pixel::getRedChroma() { return this->red_chroma; }