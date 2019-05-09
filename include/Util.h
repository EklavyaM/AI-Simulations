#pragma once

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

class Util
{
public:
    enum LogLevel
    {
        Info,
        Warning,
        Error
    };

    static float degToRad(float deg);
    static float radToDeg(float rad);
    static float getMagnitude(sf::Vector2f v);

    static float getDotProduct(sf::Vector2f a, sf::Vector2f b);
    static float getAngle(sf::Vector2f a, sf::Vector2f b);

    static float getDistance(sf::Vector2f a, sf::Vector2f b);
    static float getRootDistance(float a, float b, float maxDistance);

    static void log(LogLevel logLevel, const char *message);

    static float lerp(float a, float b, float t);
};
