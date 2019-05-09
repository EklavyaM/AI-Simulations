#pragma once

#include <SFML/System.hpp>

class ISimulatable
{
public:
    virtual void draw(sf::RenderWindow *window) = 0;
    virtual void update(float deltaTime) = 0;
};