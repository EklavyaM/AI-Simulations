#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include "IParticle.h"

class TestObject : public IParticle
{
private:
    sf::Vector2f forward;
    float alpha;

protected:
    sf::RectangleShape *RectangularBound;

    sf::Vector2f position;
    sf::Color shapeColor;

    static float speedMin, speedMax;
    static float sizeMin, sizeMax;
    static float alphaMin, alphaMax;

    float moveSpeed;
    float rotationSpeed;

public:
    TestObject(int width, int height, sf::Vector2f position,
               float moveSpeed, float rotationSpeed, sf::Color color);

    TestObject(int width, int height, sf::Vector2f position,
               float moveSpeed, float rotationSpeed, sf::Color color,
               const sf::Texture &texture);

    void draw(sf::RenderWindow *window) override;
    void update(float deltaTime) override;

    void setPosition(int x, int y) override;
    void setSize(int width, int height) override;

    void setColor(sf::Color &color) override;

    static void setParameters(float sizeMin, float sizeMax,
                              float speedMin, float speedMax,
                              float alphaMin, float alphaMax);

protected:
    TestObject(int width, int height, sf::Vector2f position,
               float moveSpeed, float rotationSpeed);

    void handleMovement(float deltaTime, sf::Vector2f mousePos);
    void handleRotation(float deltaTime, sf::Vector2f mousePos, sf::Vector2f relativeVector);

    static float getAlphaBySpeed(float speed);
    static float getAlphaBySize(float size);
};