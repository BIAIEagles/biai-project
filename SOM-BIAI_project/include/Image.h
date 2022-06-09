#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#include "Pixel.h"

namespace SOM {
class Image {
   private:
    cv::Mat BGRImageHandle;
    cv::Mat YCbCrImageHandle;
    std::vector<Pixel> pixelArray;

   public:
    Image() { this->BGRImageHandle = cv::Mat();
        this->YCbCrImageHandle = cv::Mat();
    }
    Image(std::string filename);
    Image(cv::Mat BGRImageHandle);
    Image(std::vector<Pixel> pixelArray) {
        this->pixelArray = pixelArray;
        this->BGRImageHandle = cv::Mat();
        this->YCbCrImageHandle = cv::Mat();
        transformPixelArrayToImage();
        transformYCbCr2BGR();
    }
    void setBGRImageHandle(cv::Mat handle);
    void setYCbCrImageHandle(cv::Mat handle);
    cv::Mat getBGRImageHandle();
    cv::Mat getYCbCrImageHandle();
    void transformBGR2YCbCr();
    void transformYCbCr2BGR();
    void saveToFile(std::string newFilename);
    std::vector<Pixel> getPixelArray();
    void setPixelArray(std::vector<Pixel> pixelArray);
    void transformPixelArrayToImage();
    void transformImageToPixelArray();
};
}  // namespace SOM