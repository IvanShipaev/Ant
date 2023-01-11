/**
 * \file main.c
 * \author Ivan Shiopaev
 * \brief Number of allowed cages for an ant
 */

#include <iostream>
#include <unordered_map>

/**
 * Initialize value
 */
static constexpr int32_t startX = 1000;
static constexpr int32_t startY = 1000;
static constexpr uint32_t maxSumDigit = 25;

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
    std::size_t operator()(const Point& p) const
    {
        uint64_t t = p.x;
        t = (t << 32) | p.y;
        return std::hash<uint64_t>()(t);
    }
};

static std::unordered_map<Point, bool, PointHasher> validStep; /// Map of allowed moves
static std::unordered_map<Point, bool, PointHasher> usedStep;  /// Map of completed moves

/**
 * @brief The sum of the digits in a number
 * @param value - Number
 * @return Sum
 */
static uint32_t getSumDig(int32_t value)
{
    uint32_t sum = 0;
    value = abs(value);
    while(value) {
        sum += value % 10;
        value /= 10;
    }
    return sum;
}

/**
 * @brief Checks and adds the next move if it is new and valid
 * @param x - X position
 * @param y - Y position
 */
static void tryStep(int32_t x, int32_t y)
{
    Point point(x, y);
    if( getSumDig(x) + getSumDig(y) <= maxSumDigit &&
        validStep.find(point) == validStep.end() &&
        usedStep.find(point) == usedStep.end())
    {
        validStep[point] = true;
    }
}

int main ()
{
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

    std::cout << "Number: " << usedStep.size() << std::endl;
}
