#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

#include "ISimulatable.h"

class TestObject : public ISimulatable
{
public:
    enum Type
    {
        Color,
        Texture
    };

private:
    Type testObjectType;
    sf::Vector2f forward;
    float lastFrameAcceleration;
    float alpha;

protected:
    sf::Vector2f position;
    sf::RectangleShape *RectangularBound;
    sf::Color shapeColor;

    float moveSpeed;
    float rotationSpeed;
    float angularAcceleration;
    float moveSpeedAcceleration;

public:
    TestObject(int width, int height, sf::Vector2f position, float moveSpeed, float rotationSpeed, sf::Color color);
    TestObject(int width, int height, sf::Vector2f position, float moveSpeed, float rotationSpeed, sf::Color color, const sf::Texture &texture);

    void draw(sf::RenderWindow *window) override;
    void update(sf::Time deltaTime) override;

protected:
    TestObject(int width, int height, sf::Vector2f position, float moveSpeed, float rotationSpeed);

    void handleMovement(sf::Time deltaTime, sf::Vector2f mousePos);
    void handleRotation(sf::Time deltaTime, float currentAngle, float targetAngle);
    float getAlpha();
};