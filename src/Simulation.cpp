#include "Simulation.h"

Simulation::Simulation(int width, int height, const char *title) : Application(width, height, title) {}

void Simulation::processInput()
{
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void Simulation::update(sf::Time deltaTime)
{
    for (ISimulatable *simulatable : simulatables)
        simulatable->update(deltaTime);
}

void Simulation::render()
{
    window->clear();

    for (ISimulatable *simulatable : simulatables)
        simulatable->draw(window);

    window->display();
}

void Simulation::addSimulatable(ISimulatable *simulatable)
{
    simulatables.push_back(simulatable);
}