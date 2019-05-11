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

    generateParticles(numberOfParticles);
}

ParticleGenerator::~ParticleGenerator()
{
    removeAllParticles();
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

    resetAllParticles();
}

void ParticleGenerator::removeAllParticles()
{
    while (!particleList.empty())
        delete particleList.front(), particleList.pop_front();
}

void ParticleGenerator::resetAllParticles()
{
    TestObject *testObject;
    int size, moveSpeed, rotSpeed;

    for (IParticle *particle : particleList)
    {
        testObject = (TestObject *)particle;

        size = rand() % (maxParticleSize - minParticleSize) + minParticleSize;
        moveSpeed = rand() % (maxParticleMovementSpeed - minParticleMovementSpeed) + minParticleMovementSpeed;
        rotSpeed = rand() % (maxParticleRotationSpeed - minParticleRotationSpeed) + minParticleRotationSpeed;

        testObject->setSize(size, size);
        testObject->setMoveSpeed(moveSpeed);
        testObject->setRotationSpeed(rotSpeed);
        testObject->setParameters(minParticleSize, maxParticleSize, minParticleMovementSpeed, maxParticleMovementSpeed, minParticleAlpha, maxParticleAlpha);
    }
}

void ParticleGenerator::generateParticles(int numberOfParticles)
{
    removeAllParticles();

    IParticle *particle;
    for (int i = 0; i < numberOfParticles; i++)
    {
        particle = new TestObject(this->previousColor, particleTexture);
        ((TestObject *)particle)->setPosition(rand() % boundaryWidth, rand() % boundaryHeight);
        particleList.push_front(particle);
    }
}