#include "../include/Image.h"

using namespace SOM;

Image::Image(cv::Mat BGRImageHandle) {
    this->BGRImageHandle = BGRImageHandle;
    this->transformBGR2YCbCr();
}

Image::Image(std::string filename) { this->setBGRImageHandle(filename); }

void Image::transformBGR2YCbCr() {
    cv::cvtColor(this->BGRImageHandle, this->YCbCrImageHandle,
                 cv::COLOR_BGR2YCrCb);
}

void Image::transformYCbCr2BGR() {
    cv::cvtColor(this->YCbCrImageHandle, this->BGRImageHandle,
                 cv::COLOR_YCrCb2BGR);
}

void Image::saveToFile(std::string newFilename) {
    this->transformYCbCr2BGR();
    cv::imwrite(newFilename, this->BGRImageHandle);
}

std::vector<Pixel> SOM::Image::getPixelArray() { return this->pixelArray; }

void SOM::Image::setPixelArray(std::vector<Pixel> pixelArray) {
    this->pixelArray = pixelArray;
}

void SOM::Image::transformPixelArrayToImage() { 
    static uint8_t *bitmap;
    bitmap = (uint8_t *)malloc(this->pixelArray.size() * sizeof(uint8_t) * 3);
    if (bitmap == nullptr) {
        return;
    }
    for (int i = 0; i < this->pixelArray.size(); i++) {
        bitmap[i] = pixelArray[i].getBrightness();
        bitmap[i + 1] = pixelArray[i].getBlueChroma();
        bitmap[i + 2] = pixelArray[i].getRedChroma();
    }
    cv::Mat tempImageYCbCr(sqrt(this->pixelArray.size()), sqrt(this->pixelArray.size()), CV_8UC3, bitmap);
    this->YCbCrImageHandle = tempImageYCbCr;
    free(bitmap);
}

void Image::setBGRImageHandle(std::string filename) {
    this->BGRImageHandle = cv::imread(filename);
}