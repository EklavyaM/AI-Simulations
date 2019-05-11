#include "Util.h"

float Util::sqrt(float x)
{
    unsigned int i = *(unsigned int *)&x;
    i += 127 << 23;
    i >>= 1;
    return *(float *)&i;
}

float Util::degToRad(float deg)
{
    return deg * (M_PI / 180);
}

float Util::radToDeg(float rad)
{
    return 180 * rad / M_PI;
}

float Util::getAngle(sf::Vector2f a, sf::Vector2f b)
{
    float magA = getMagnitude(a);
    float magB = getMagnitude(b);
    if (magA == 0 || magB == 0)
        return 0;
    return acos(getDotProduct(a, b) / magA * magB);
}

float Util::getMagnitude(sf::Vector2f v)
{
    return Util::sqrt(v.x * v.x + v.y * v.y);
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

float Util::lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}