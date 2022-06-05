#pragma once
#include "./SOMNetwork.h"
#include "./SubframeCompressed.h"
namespace SOM {
	class SOMNetworkEncoder {
		private:
			SOMNetwork network;
	
		public:
            SOMNetworkEncoder(SOMNetwork network);
            std::vector<std::vector<SubframeCompressed>> encode(
                     std::vector<std::vector<Subframe>> frames);
	};
}