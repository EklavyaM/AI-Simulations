#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Application
{
protected:
    const int FRAME_RATE = 60;
    sf::RenderWindow *window;

public:
    Application() = delete;
    Application(int width, int height, const char *title);
    ~Application();

    void run();

protected:
    virtual void processInput() = 0;
    virtual void update(sf::Time deltaTime) = 0;
    virtual void render() = 0;
};