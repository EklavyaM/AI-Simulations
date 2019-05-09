#pragma once

#include <list>

#include <SFML/Graphics.hpp>
#include "ISimulatable.h"
#include "IParticle.h"

class ParticleGenerator : public ISimulatable
{
private:
    int boundaryWidth;
    int boundaryHeight;

    float frameCounter;
    float colorChangeDelay;

    sf::Color previousColor;
    sf::Color nextColor;

protected:
    std::list<IParticle *> particleList;

    sf::Color particleColor;
    sf::Texture particleTexture;

    int maxParticleSize, minParticleSize;
    int maxParticleMovementSpeed, minParticleMovementSpeed;
    int maxParticleRotationSpeed, minParticleRotationSpeed;
    int minParticleAlpha, maxParticleAlpha;

public:
    void draw(sf::RenderWindow *window) override;
    void update(float deltaTime) override;

    void setParticleColor(sf::Color color);

    ParticleGenerator() = delete;
    ParticleGenerator(int boundaryWidth, int boundaryHeight,
                      int numberOfParticles, sf::Color startingColor,
                      const sf::Texture &particleTexture, float colorChangeDelay);

private:
    void lerpTowardsNextColor(float deltaTime);
    void setParticleParameters(float minSize, float maxSize, float minMoveSpeed,
                               float maxMoveSpeed, float minRotSpeed, float maxRotSpeed,
                               float minAlpha, float maxAlpha);
    void generateParticles(int numberOfParticles);

    static sf::Color getRandomColor();
};