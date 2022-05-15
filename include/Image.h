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
    Image();
    Image(std::string filename);
    Image(cv::Mat BGRImageHandle);
    void setBGRImageHandle(std::string filename);
    void transformBGR2YCbCr();
    void saveToFile(std::string newFilename);
};
}  // namespace SOM