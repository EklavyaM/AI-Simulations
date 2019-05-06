#include "Util.h"

float Util::degToRad(float deg)
{
    return M_PI / 180 * deg;
}

float Util::radToDeg(float rad)
{
    return 180 * rad / M_PI;
}

float Util::getAngle(sf::Vector2f a, sf::Vector2f b)
{
    return acos(getDotProduct(a, b) / (getMagnitude(a) * getMagnitude(b)));
}

float Util::getMagnitude(sf::Vector2f v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

float Util::getDistance(sf::Vector2f a, sf::Vector2f b)
{
    return Util::getMagnitude(sf::Vector2f(pow(a.x - b.x, 2), pow(a.y - b.y, 2)));
}

float Util::getRootDistance(float a, float b, float maxDistance)
{
    float value = 1.f / pow(b - a, 2);

    if (value >= maxDistance)
    {
        return maxDistance;
    }
    return value;
}

float Util::getDotProduct(sf::Vector2f a, sf::Vector2f b)
{
    return a.x * b.x + a.y * b.y;
}

void Util::log(Util::LogLevel logLevel, const char *message)
{
    switch (logLevel)
    {
    case LogLevel::Info:
        std::cout << "[INFO]: " << message << std::endl;
        break;
    case LogLevel::Warning:
        std::cout << "[WARNING]: " << message << std::endl;
        break;
    case LogLevel::Error:
        std::cout << "[ERROR]: " << message << std::endl;
        break;
    }
}