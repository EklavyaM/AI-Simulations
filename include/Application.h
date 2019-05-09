#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Application
{
protected:
    int frameRate = 60;
    sf::RenderWindow *window;

public:
    Application() = delete;
    Application(int width, int height, const char *title, int frameRate);
    ~Application();

    void run();

protected:
    virtual void processInput() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
};