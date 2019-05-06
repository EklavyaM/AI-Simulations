#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>

#include "Util.h"

#include "Simulation.h"
#include "TestObject.h"

#define WIDTH 1366
#define HEIGHT 768

int main()
{

	sf::Texture testObjectTexture;
	if (!testObjectTexture.loadFromFile("img/blue_flare.jpg"))
	{
		Util::log(Util::LogLevel::Error, "texture not loaded!");
		return -1;
	};

	Simulation sim(WIDTH, HEIGHT, "Flock Simulation", 60);

	srand(time(0));

	int size;

	for (int i = 0; i < 100; i++)
	{
		size = rand() % 320 + 10;
		sim.addSimulatable(new TestObject(size,
										  size,
										  sf::Vector2f(rand() % WIDTH, rand() % HEIGHT),
										  rand() % 15 + 10,
										  rand() % 200 * 0.01,
										  sf::Color(170, 104, 60),
										  testObjectTexture));
	}

	sim.run();

	return 0;
}
