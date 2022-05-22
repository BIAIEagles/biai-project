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

void Image::setBGRImageHandle(std::string filename) {
    this->BGRImageHandle = cv::imread(filename);
}