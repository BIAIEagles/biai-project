#include "../include/Image.h"

using namespace SOM;

Image::Image(cv::Mat BGRImageHandle) {
    this->BGRImageHandle = BGRImageHandle;
    this->transformBGR2YCbCr();
}

Image::Image(std::string filename) {
    this->BGRImageHandle = cv::imread(filename);
    this->YCbCrImageHandle = BGRImageHandle;
}

void Image::transformBGR2YCbCr() {
    cv::cvtColor(this->BGRImageHandle, this->YCbCrImageHandle,
                 cv::COLOR_BGR2YCrCb);
}

void Image::transformYCbCr2BGR() {
    //this->BGRImageHandle = cv::Mat(this->YCbCrImageHandle, cv::COLOR_YCrCb2BGR);
     cv::cvtColor(this->YCbCrImageHandle, this->BGRImageHandle,
                 cv::COLOR_YCrCb2BGR);
}

void Image::saveToFile(std::string newFilename) {
    //this->transformYCbCr2BGR();
    this->BGRImageHandle = this->YCbCrImageHandle;
    cv::imwrite(newFilename, this->BGRImageHandle);
}

std::vector<Pixel> SOM::Image::getPixelArray() { return this->pixelArray; }

void SOM::Image::setPixelArray(std::vector<Pixel> pixelArray) {
    this->pixelArray = pixelArray;
}

void SOM::Image::transformPixelArrayToImage() {
    YCbCrImageHandle.create(sqrt(pixelArray.size()), sqrt(pixelArray.size()),
                               CV_8UC3);
    int width = sqrt(pixelArray.size()) * 3;
    int height = sqrt(pixelArray.size());
    int pxIndex = 0;
    unsigned char *dataP;
    for (int i = 0; i < height; i++) {
        dataP = YCbCrImageHandle.ptr<unsigned char>(i);
        for (int j = 0; j < width-2; j+=3) {
            int lumaValue = this->pixelArray[pxIndex]
                    .getBrightness();
            int redChromaValue = this->pixelArray[pxIndex]
                                .getRedChroma();
            int blueChromaValue = this->pixelArray[pxIndex]
                                .getBlueChroma();
            dataP[j] = lumaValue;
            dataP[j+1] = redChromaValue;
            dataP[j+2] = blueChromaValue;
            pxIndex++;
        }
    }
    cv::Mat temp = cv::Mat();
    temp.create(400, 400, CV_8UC3);
    //cv::cvtColor(this->YCbCrImageHandle, temp, cv::COLOR_YCrCb2BGR, 3);
    cv::imwrite("test_ycbcr.jpg", this->YCbCrImageHandle);
    /* static uint8_t *bitmap;
    bitmap = (uint8_t *)malloc(this->pixelArray.size() * sizeof(uint8_t) * 3);
    if (bitmap == nullptr) {
        return;
    }
    for (int i = 0; i < this->pixelArray.size(); i++) {
        bitmap[i] = pixelArray[i].getBrightness();
        bitmap[i + 1] = pixelArray[i].getBlueChroma();
        bitmap[i + 2] = pixelArray[i].getRedChroma();
    }
    cv::Mat tempImageYCbCr(sqrt(this->pixelArray.size()),
                           sqrt(this->pixelArray.size()), CV_8SC3, bitmap);*/
    //this->YCbCrImageHandle = tempImageYCbCr;
}

void SOM::Image::transformImageToPixelArray() {
    int width = YCbCrImageHandle.cols * YCbCrImageHandle.channels();
    int height = YCbCrImageHandle.rows;
    std::vector<Pixel> tpixelArray;
    unsigned char *dataP;
    int pxIndex = 0;
    for (int i = 0; i < height; i++) {
        dataP = YCbCrImageHandle.ptr<unsigned char>(i);
        for (int j = 0; j < width - 2; j+=3) {
            int lumaValue = dataP[j];
            int redChromaValue = dataP[j + 2];
            int blueChromaValue = dataP[j + 1];
            Pixel temp;
            temp.setBrightness(lumaValue);
            temp.setRedChroma(redChromaValue);
            temp.setBlueChroma(blueChromaValue);
            tpixelArray.push_back(temp);
        }
    }
    /* std::vector<Pixel> flattenedPixelArray;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / YCbCrImageHandle.channels(); j++) {
            flattenedPixelArray.push_back(tpixelArray[i][j]);
        }    
    }*/
    this->pixelArray = tpixelArray;
}

void Image::setBGRImageHandle(cv::Mat handle) { this->BGRImageHandle = handle; }

void SOM::Image::setYCbCrImageHandle(cv::Mat handle) {
    this->YCbCrImageHandle = handle;
}

cv::Mat SOM::Image::getBGRImageHandle() { return this->BGRImageHandle; }

cv::Mat SOM::Image::getYCbCrImageHandle() { return this->YCbCrImageHandle; }
