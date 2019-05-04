#include "Application.h"

Application::Application(int width, int height, const char *title)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default, settings);
}

Application::~Application()
{
    delete window;
}

void Application::run()
{

    sf::Clock gameClock;
    sf::Time timePerFrame = sf::seconds(1.f / FRAME_RATE);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    sf::Time timeSleep;

    while (window->isOpen())
    {
        processInput();
        timeSinceLastUpdate += gameClock.restart();

        if (timeSinceLastUpdate < timePerFrame)
            timeSleep = timePerFrame - timeSinceLastUpdate;

        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            processInput();
            update(timePerFrame);
        }

        sf::sleep(timeSleep);

        render();
    }
}