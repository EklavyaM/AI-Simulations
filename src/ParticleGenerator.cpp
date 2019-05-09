#include <ctime>
#include <iostream>

#include "ParticleGenerator.h"
#include "TestObject.h"
#include "Util.h"

ParticleGenerator::ParticleGenerator(int boundaryWidth, int boundaryHeight,
                                     int numberOfParticles, sf::Color startingColor,
                                     const sf::Texture &particleTexture, float colorChangeDelay)
{
    this->boundaryWidth = boundaryWidth;
    this->boundaryHeight = boundaryHeight;

    this->particleColor = startingColor;
    this->particleTexture = particleTexture;
    this->colorChangeDelay = colorChangeDelay;
    this->previousColor = startingColor;
    this->nextColor = getRandomColor();

    setParticleParameters(10, 50, 1, 100, 1, 100, 60, 80);
    generateParticles(numberOfParticles);
}

void ParticleGenerator::draw(sf::RenderWindow *window)
{
    for (IParticle *particle : particleList)
        particle->draw(window);
}

void ParticleGenerator::update(float deltaTime)
{
    lerpTowardsNextColor(deltaTime);
    for (IParticle *particle : particleList)
        particle->update(deltaTime);
}

void ParticleGenerator::lerpTowardsNextColor(float deltaTime)
{
    frameCounter += deltaTime;

    if (frameCounter >= 0 && frameCounter < colorChangeDelay)
    {
        particleColor.r = Util::lerp(previousColor.r, nextColor.r, frameCounter / colorChangeDelay);
        particleColor.g = Util::lerp(previousColor.g, nextColor.g, frameCounter / colorChangeDelay);
        particleColor.b = Util::lerp(previousColor.b, nextColor.b, frameCounter / colorChangeDelay);
    }
    else
    {
        frameCounter = 0;
        previousColor = nextColor;
        nextColor = getRandomColor();
    }
    setParticleColor(particleColor);
}

void ParticleGenerator::setParticleColor(sf::Color color)
{
    for (IParticle *particle : particleList)
        particle->setColor(color);

    particleColor = color;
}

sf::Color ParticleGenerator::getRandomColor()
{
    sf::Color color(rand() % 255, rand() % 255, rand() % 255);
    return color;
}

void ParticleGenerator::setParticleParameters(float minSize, float maxSize,
                                              float minMoveSpeed, float maxMoveSpeed,
                                              float minRotSpeed, float maxRotSpeed,
                                              float minAlpha, float maxAlpha)
{
    this->minParticleSize = minSize;
    this->maxParticleSize = maxSize;

    this->minParticleMovementSpeed = minMoveSpeed;
    this->maxParticleMovementSpeed = maxMoveSpeed;

    this->minParticleRotationSpeed = minRotSpeed;
    this->maxParticleRotationSpeed = maxRotSpeed;

    this->minParticleAlpha = minAlpha;
    this->maxParticleAlpha = maxAlpha;
}

void ParticleGenerator::generateParticles(int numberOfParticles)
{
    particleList.clear();

    IParticle *particle;
    int size;

    srand(time(0));
    for (int i = 0; i < numberOfParticles; i++)
    {
        size = (rand() % (maxParticleSize - minParticleSize) + minParticleSize);
        particle = new TestObject(size,
                                  size,
                                  sf::Vector2f(rand() % boundaryWidth, rand() % boundaryHeight),
                                  rand() % (maxParticleMovementSpeed - minParticleMovementSpeed) + minParticleMovementSpeed,
                                  rand() % (maxParticleRotationSpeed - minParticleRotationSpeed) + minParticleRotationSpeed,
                                  this->previousColor,
                                  particleTexture);
        particleList.push_front(particle);
    }

    TestObject::setParameters(minParticleSize, maxParticleSize,
                              minParticleMovementSpeed, maxParticleMovementSpeed,
                              minParticleAlpha, maxParticleAlpha);
}