#include "Application.h"

Application::Application(int width, int height, const char *title, int frameRate)
{
    this->frameRate = frameRate;
    window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Fullscreen);
}

Application::~Application()
{
    delete window;
}

void Application::run()
{

    sf::Clock gameClock;
    sf::Time timePerFrame = sf::seconds(1.f / frameRate);
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
            update(timePerFrame.asSeconds());
        }

        sf::sleep(timeSleep);

        render();
    }
}