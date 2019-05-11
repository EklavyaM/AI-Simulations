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
    ParticleGenerator() = delete;
    ~ParticleGenerator();
    ParticleGenerator(int boundaryWidth, int boundaryHeight,
                      int numberOfParticles, sf::Color startingColor,
                      const sf::Texture &particleTexture, float colorChangeDelay);

    void draw(sf::RenderWindow *window) override;
    void update(float deltaTime) override;
    void removeAllParticles();
    void resetAllParticles();
    void setParticleColor(sf::Color color);
    void setParticleParameters(float minSize, float maxSize, float minMoveSpeed,
                               float maxMoveSpeed, float minRotSpeed, float maxRotSpeed,
                               float minAlpha, float maxAlpha);

private:
    static sf::Color getRandomColor();

    void lerpTowardsNextColor(float deltaTime);
    void generateParticles(int numberOfParticles);
};