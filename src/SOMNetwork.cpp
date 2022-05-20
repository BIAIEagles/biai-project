#include "../include/SOMNetwork.h"

using namespace SOM;

SOMNetwork::SOMNetwork(int neuronsCount, int weightsCount, double step,
                       int minWinnerCounter) {
    this->trainingStep = step;
    this->minWinnerCounter = minWinnerCounter;

    for (int i = 0; i < neuronsCount; i++) {
    }
}