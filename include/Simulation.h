#pragma once

#include <list>

#include "Application.h"
#include "ISimulatable.h"

class Simulation : public Application
{

public:
    static sf::Vector2i mousePosition;

private:
    sf::Event event;
    std::list<ISimulatable *> simulatables;

public:
    Simulation(int width, int height, const char *title, int frameRate);
    void addSimulatable(ISimulatable *simulatable);

private:
    void processInput() override;
    void update(sf::Time deltaTime) override;
    void render() override;
};
