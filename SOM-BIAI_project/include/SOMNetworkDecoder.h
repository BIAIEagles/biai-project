#pragma once

#include "./SOMNetwork.h"
#include "./SubframeCompressed.h"
#include "./Subframe.h"


namespace SOM {
class SOMNetworkDecoder {
   private:
    SOMNetwork network;
    int width;
    int height;
    int frameWidth;
    int frameHeight;
    std::vector<Pixel> pixelArray;
    std::vector<std::vector<SubframeCompressed>> encodedFrames;

   public:
    SOMNetworkDecoder(SOMNetwork network,
                      std::vector<std::vector<SubframeCompressed>> encodedFrames, int width,
                      int height, int frameWidth, int frameHeight);
    std::vector<Pixel> decode();
    void recodePixels(std::vector<int> subData, colorPart colorChoice,
                      int startPosX, int startPosY);
};
}