#include <iostream>
#include <string>

#include "TestObject.h"
#include "Simulation.h"

#include "Util.h"

TestObject::TestObject(sf::Color color)
{
    RectangularBound = new sf::RectangleShape();
}

TestObject::TestObject(sf::Color color, const sf::Texture &texture) : TestObject(color)
{
    RectangularBound->setTexture(&texture);
}

TestObject::~TestObject()
{
    delete RectangularBound;
}

void TestObject::draw(sf::RenderWindow *window)
{
    this->shapeColor.a = getAlphaBySpeed(moveSpeed);
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

    while (diff < -M_PI)
        diff += 2 * M_PI;
    while (diff > M_PI)
        diff -= 2 * M_PI;

    if (diff > 0.05f)
        RectangularBound->rotate(rotDist * deltaTime * rotationSpeed);
    else if (diff < -0.05f)
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
    alpha /= (sizeMax - sizeMin);
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

void TestObject::setMoveSpeed(float moveSpeed)
{
    this->moveSpeed = moveSpeed;
}

void TestObject::setRotationSpeed(float rotationSpeed)
{
    this->rotationSpeed = rotationSpeed;
}

void TestObject::setParameters(float sizeMin, float sizeMax,
                               float speedMin, float speedMax,
                               float alphaMin, float alphaMax)
{
    this->sizeMin = sizeMin;
    this->sizeMax = sizeMax;

    this->speedMin = speedMin;
    this->speedMax = speedMax;

    this->alphaMin = alphaMin;
    this->alphaMax = alphaMax;
}