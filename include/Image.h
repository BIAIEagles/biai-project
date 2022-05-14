#include <opencv2/opencv.hpp>
#include <string>

namespace SOM {
class Image {
   private:
    cv::Mat BGRImageHandle;
    cv::Mat YCbCrImageHandle;

   public:
    Image();
    Image(std::string filename);
    Image(cv::Mat BGRImageHandle);
};
}  // namespace SOM