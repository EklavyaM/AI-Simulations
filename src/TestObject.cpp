#include <iostream>
#include <string>

#include "TestObject.h"
#include "Simulation.h"

#include "Util.h"

float TestObject::speedMin;
float TestObject::speedMax;
float TestObject::sizeMin;
float TestObject::sizeMax;
float TestObject::alphaMin;
float TestObject::alphaMax;

TestObject::TestObject(int width, int height, sf::Vector2f position,
                       float moveSpeed, float rotationSpeed)
{
    RectangularBound = new sf::RectangleShape(sf::Vector2f(width, height));
    RectangularBound->setPosition(position);

    this->moveSpeed = moveSpeed;
    this->rotationSpeed = rotationSpeed;
}

TestObject::TestObject(int width, int height, sf::Vector2f position,
                       float moveSpeed, float rotationSpeed, sf::Color color)
    : TestObject(width, height, position, moveSpeed, rotationSpeed)
{
    this->shapeColor = color;
}

TestObject::TestObject(int width, int height, sf::Vector2f position,
                       float moveSpeed, float rotationSpeed,
                       sf::Color color, const sf::Texture &texture)
    : TestObject(width, height, position, moveSpeed, rotationSpeed)
{
    this->shapeColor = color;
    RectangularBound->setTexture(&texture);
}

void TestObject::draw(sf::RenderWindow *window)
{
    this->shapeColor.a = getAlphaBySpeed(moveSpeed);

    /* std::cout << (int)shapeColor.r << ", "
              << (int)shapeColor.g << ", "
              << (int)shapeColor.b << ", "
              << (int)shapeColor.a << std::endl; */

    RectangularBound->setFillColor(this->shapeColor);
    window->draw(*RectangularBound, sf::BlendAdd);
}

void TestObject::update(float deltaTime)
{
    sf::Vector2f mousePos = (sf::Vector2f)Simulation::mousePosition;
    sf::Vector2f relativeVector = mousePos - RectangularBound->getPosition();

    handleRotation(deltaTime, mousePos, relativeVector);
    handleMovement(deltaTime, mousePos);
}

void TestObject::handleMovement(float deltaTime, sf::Vector2f mousePos)
{
    RectangularBound->move(deltaTime * moveSpeed * forward);
}

void TestObject::handleRotation(float deltaTime, sf::Vector2f mousePos,
                                sf::Vector2f relativeVector)
{
    float rot = Util::degToRad(RectangularBound->getRotation());

    forward = sf::Vector2f(cos(rot), sin(rot));
    float rotDist = Util::getAngle(relativeVector, forward);

    float targetAngle = atan2(relativeVector.y, relativeVector.x);
    float diff = targetAngle - rot;

    // Make sure you turn less than 180 degree
    while (diff < -M_PI)
        diff += 2 * M_PI;
    while (diff > M_PI)
        diff -= 2 * M_PI;

    if (diff > 0)
        RectangularBound->rotate(rotDist * deltaTime * rotationSpeed);
    else if (diff < 0)
        RectangularBound->rotate(-rotDist * deltaTime * rotationSpeed);
}

float TestObject::getAlphaBySpeed(float speed)
{
    float alpha = (speed - speedMin) * (alphaMax - alphaMin);
    alpha /= (speedMax - speedMin);
    alpha += alphaMin;
    return alpha;
}

float TestObject::getAlphaBySize(float size)
{
    float alpha = (size - sizeMin) * (alphaMax - alphaMin);
    alpha /= (sizeMin - sizeMax);
    alpha += alphaMin;
    return alpha;
}

void TestObject::setPosition(int x, int y)
{
    RectangularBound->setPosition(x, y);
}

void TestObject::setSize(int width, int height)
{
    RectangularBound->setSize(sf::Vector2f(width, height));
}

void TestObject::setColor(sf::Color &color)
{
    this->shapeColor = color;
}

void TestObject::setParameters(float sizeMin, float sizeMax,
                               float speedMin, float speedMax,
                               float alphaMin, float alphaMax)
{
    TestObject::sizeMin = sizeMin;
    TestObject::sizeMax = sizeMax;

    TestObject::speedMin = speedMin;
    TestObject::speedMax = speedMax;

    TestObject::alphaMin = alphaMin;
    TestObject::alphaMax = alphaMax;
}