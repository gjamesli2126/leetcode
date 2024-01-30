#include <iostream>
#include <vector>
#include <algorithm>

int maxPlanesShotDown(std::vector<int> startHeight, std::vector<int> descentRate) {
    std::vector<int> timeToLand;
    // Calculate the time to land for each plane
    for (size_t i = 0; i < startHeight.size(); ++i) {
        timeToLand.push_back((startHeight[i] + descentRate[i] - 1) / descentRate[i]);
    }

    // Sort the times to find the maximum number of planes that can be shot down
    std::sort(timeToLand.begin(), timeToLand.end());//ascending

    int maxPlanes = 0;
    for (size_t i = 0; i < timeToLand.size() && maxPlanes < timeToLand[i]; ++i) {
        ++maxPlanes;
    }

    return maxPlanes;
}

int main() {
    std::vector<int> startHeight = {1, 3, 5, 4, 8};
    std::vector<int> descentRate = {1, 2, 2, 1, 2};

    std::cout << "Maximum number of planes that can be shot down: "
              << maxPlanesShotDown(startHeight, descentRate) << std::endl;
    startHeight = {1, 2, 3, 4, 5};

    std::cout << "Maximum number of planes that can be shot down: "
              << maxPlanesShotDown(startHeight, descentRate) << std::endl;

    return 0;
}
