#include "Simulation.h"

sf::Vector2i Simulation::mousePosition;

Simulation::Simulation(int width, int height, const char *title, int frameRate) : Application(width, height, title, frameRate) {}

Simulation::~Simulation()
{
    while (!simulatables.empty())
        delete simulatables.front(), simulatables.pop_front();
}

void Simulation::processInput()
{
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }

    mousePosition = sf::Mouse::getPosition(*window);
}

void Simulation::update(float deltaTime)
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