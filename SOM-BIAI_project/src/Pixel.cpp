#include "../include/Pixel.h"

SOM::Pixel::Pixel(double brightness, double blue_chroma, double red_chroma) {
    this->brightness = brightness;
    this->blue_chroma = blue_chroma;
    this->red_chroma = red_chroma;
}

SOM::Pixel::Pixel() {
    this->brightness = 0;
    this->blue_chroma = 0;
    this->red_chroma = 0;
}

void SOM::Pixel::setBrightness(double brightness) {
    this->brightness = brightness;
}

double SOM::Pixel::getBrightness() { return this->brightness; }

void SOM::Pixel::setBlueChroma(double blue_chroma) {
    this->blue_chroma = blue_chroma;
}

double SOM::Pixel::getBlueChroma() { return this->blue_chroma; }

void SOM::Pixel::setRedChroma(double red_chroma) {
    this->red_chroma = red_chroma;
}

double SOM::Pixel::getRedChroma() { return this->red_chroma; }