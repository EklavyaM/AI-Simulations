#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

#include "ISimulatable.h"
#include "Util.h"

class TestObject : public ISimulatable
{
protected:
    sf::Vector2f position;
    sf::RectangleShape *line;
    sf::Vector2f forward;

public:
    TestObject();

    void rotate(float rot);

    void draw(sf::RenderWindow *window) override;
    void update(sf::Time deltaTime) override;
};