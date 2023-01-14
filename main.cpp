/**
 * \file main.c
 * \author Ivan Shipaev
 * \brief Number of allowed cages for an ant
 */

#include <cstdint>
#include <iostream>
#include <unordered_map>

/**
 *  Struct Point
 */
struct Point
{
    int32_t x, y;
    Point(int32_t x, int32_t y) : x(x), y(y) {};
    bool operator==(const Point &p) const
    {
        return (x == p.x && y == p.y) ? true : false;
    }
};

/**
 *  Struct Point Hasher
 */
struct PointHasher
{
    size_t operator()(const Point& p) const
    {
        uint64_t t = p.x;
        t = (t << 32) | p.y;
        return std::hash<uint64_t>()(t);
    }
};

/**
 * @param startX - start position X
 * @param startY - start position Y
 * @param maxSumDigit - max sum digits X and Y
 * @return Number of moves of the ant
 */
size_t getStepsAnt(const int32_t startX, const int32_t startY, const uint32_t maxSumDigit)
{
    std::unordered_map<Point, bool, PointHasher> validStep; /// Hash map of allowed moves
    std::unordered_map<Point, bool, PointHasher> usedStep;  /// Hash map of completed moves

    auto tryStep = [&maxSumDigit, &validStep, &usedStep] (int32_t x, int32_t y) {
        Point point(x, y);
        auto getSumDig = [] (int32_t value) {
            uint32_t sum = 0;
            value = std::abs(value);
            while(value) {
                sum += value % 10;
                value /= 10;
            }
            return sum;
        };
        if( getSumDig(x) + getSumDig(y) <= maxSumDigit &&
            validStep.find(point) == validStep.end() &&
            usedStep.find(point) == usedStep.end())
        {
            validStep[point] = true;
        }
    };

    tryStep(startX, startY);
    auto it = validStep.begin();
    while(it != validStep.end()) {
        Point point = it->first;

        usedStep.insert(*it);
        validStep.erase(it);

        tryStep(point.x+1, point.y);
        tryStep(point.x-1, point.y);
        tryStep(point.x, point.y+1);
        tryStep(point.x, point.y-1);

        it = validStep.begin();
    }

    return usedStep.size();
}

int main ()
{
    std::cout << "Number: " << getStepsAnt(1000, 1000, 25) << std::endl;
    std::cout << "For exit press Enter or Ctrl+C" << std::endl;
    std::getchar();
    return 0;
}

