#include "TestObject.h"
#include <iostream>

TestObject::TestObject()
{
    line = new sf::RectangleShape(sf::Vector2f(20.f, 1.f));
    line->setPosition(200, 200);
}

void TestObject::draw(sf::RenderWindow *window)
{
    window->draw(*line);
}

void TestObject::update(sf::Time deltaTime)
{
    rotate(deltaTime.asSeconds() * 100);
    line->move(deltaTime.asSeconds() * 100 * forward);
}

void TestObject::rotate(float rot)
{
    line->rotate(rot);
    float rotation = Util::degToRad(line->getRotation());
    forward = sf::Vector2f(cos(rotation), sin(rotation));
}