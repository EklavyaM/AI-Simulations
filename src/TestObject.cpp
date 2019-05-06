#include <iostream>
#include <string>

#include "TestObject.h"
#include "Simulation.h"

#include "Util.h"

TestObject::TestObject(int width, int height, sf::Vector2f position,
                       float moveSpeed, float rotationSpeed)
{
    RectangularBound = new sf::RectangleShape(sf::Vector2f(width, height));
    RectangularBound->setPosition(position);

    this->moveSpeed = moveSpeed;
    this->rotationSpeed = rotationSpeed;

    lastFrameAcceleration = 0;
}

TestObject::TestObject(int width, int height, sf::Vector2f position,
                       float moveSpeed, float rotationSpeed, sf::Color color) : TestObject(width, height, position, moveSpeed, rotationSpeed)
{
    this->shapeColor = color;
    testObjectType = Type::Color;
}

TestObject::TestObject(int width, int height, sf::Vector2f position,
                       float moveSpeed, float rotationSpeed, sf::Color color,
                       const sf::Texture &texture) : TestObject(width, height, position, moveSpeed, rotationSpeed)
{
    this->shapeColor = color;
    RectangularBound->setTexture(&texture);
    testObjectType = Type::Texture;
}

void TestObject::draw(sf::RenderWindow *window)
{
    this->shapeColor.a = getAlpha();
    RectangularBound->setFillColor(this->shapeColor);
    window->draw(*RectangularBound, sf::BlendAdd);
}

void TestObject::update(sf::Time deltaTime)
{
    sf::Vector2f mousePos = (sf::Vector2f)Simulation::mousePosition;

    sf::Vector2f relativeVector = mousePos - RectangularBound->getPosition();

    handleRotation(deltaTime, RectangularBound->getRotation(), Util::radToDeg(atan2(relativeVector.y, relativeVector.x)));
    handleMovement(deltaTime, mousePos);
}

void TestObject::handleMovement(sf::Time deltaTime, sf::Vector2f mousePos)
{
    moveSpeedAcceleration = Util::getDistance(mousePos, RectangularBound->getPosition());

    if (moveSpeedAcceleration > lastFrameAcceleration)
    {
        moveSpeed += moveSpeedAcceleration * deltaTime.asSeconds() * 0.001f;
    }
    else
    {
        moveSpeed -= moveSpeedAcceleration * deltaTime.asSeconds() * 0.0005f;
    }

    lastFrameAcceleration = moveSpeedAcceleration;
    moveSpeed = moveSpeed < 60 ? moveSpeed : 60;

    RectangularBound->move(deltaTime.asSeconds() * moveSpeed * forward);
}

void TestObject::handleRotation(sf::Time deltaTime, float currentAngle, float targetAngle)
{
    if (targetAngle < 0)
        targetAngle = 360 + targetAngle;

    if (fabs(targetAngle - currentAngle) > 5)
    {
        float rotationVal = targetAngle - currentAngle;

        if (fabs(rotationVal) > 180 && fabs(rotationVal) <= 360)
            rotationVal = 360 - fabs(rotationVal);

        RectangularBound->rotate(rotationVal * deltaTime.asSeconds() * rotationSpeed);
    }

    float rotation = Util::degToRad(RectangularBound->getRotation());
    forward = sf::Vector2f(cos(rotation), sin(rotation));
}

float TestObject::getAlpha()
{
    float alpha = ((fabs(moveSpeed)) * 180) / 300;
    alpha += 40;
    return alpha;
}
