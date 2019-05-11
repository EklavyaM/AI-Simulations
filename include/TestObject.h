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

    float speedMin, speedMax;
    float sizeMin, sizeMax;
    float alphaMin, alphaMax;

    float moveSpeed;
    float rotationSpeed;

public:
    ~TestObject();
    TestObject() = delete;
    TestObject(sf::Color color);
    TestObject(sf::Color color, const sf::Texture &texture);

    void draw(sf::RenderWindow *window) override;
    void update(float deltaTime) override;

    void setPosition(int x, int y) override;
    void setSize(int width, int height) override;
    void setColor(sf::Color &color) override;
    void setMoveSpeed(float moveSpeed);
    void setRotationSpeed(float rotationSpeed);
    void setParameters(float sizeMin, float sizeMax,
                       float speedMin, float speedMax,
                       float alphaMin, float alphaMax);

protected:
    void handleMovement(float deltaTime, sf::Vector2f mousePos);
    void handleRotation(float deltaTime, sf::Vector2f mousePos, sf::Vector2f relativeVector);

    float getAlphaBySpeed(float speed);
    float getAlphaBySize(float size);
};