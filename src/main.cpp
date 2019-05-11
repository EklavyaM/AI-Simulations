#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Util.h"
#include "Simulation.h"
#include "ParticleGenerator.h"

#define WIDTH 1366
#define HEIGHT 768
#define DEFAULT_IMAGE_PATH "img/blue_flare.jpg"

bool loadDefaultTexture(sf::Texture &texture);
bool loadFileTexture(sf::Texture &texture, const char *path);
void runSimulation(const sf::Texture &texture);
sf::Color getRandomColor();

int main(int argc, char *argv[])
{
	sf::Texture testObjectTexture;
	if (argc != 2)
	{
		if (!loadDefaultTexture(testObjectTexture))
			return -1;
	}
	else if (!loadFileTexture(testObjectTexture, argv[1]))
		return -1;

	runSimulation(testObjectTexture);
	return 0;
}

void runSimulation(const sf::Texture &texture)
{
	Simulation sim(WIDTH, HEIGHT, "Flock Simulation", 60);

	srand(time(0));

	ParticleGenerator *pg;
	for (int i = 0; i < 3; i++)
	{
		pg = new ParticleGenerator(WIDTH, HEIGHT, 7000, getRandomColor(), texture, 5);

		int minSize = rand() % 10 + 10;
		int maxSize = rand() % 18 + 21;

		int minMoveSpeed = rand() % 50 + 10;
		int maxMoveSpeed = rand() % 50 + 61;

		int minRotSpeed = rand() % 5 + 5;
		int maxRotSpeed = rand() % 10 + 11;

		int minAlpha = rand() % 30 + 20;
		int maxAlpha = rand() % 30 + 50;

		pg->setParticleParameters(minSize, maxSize,
								  minMoveSpeed, maxMoveSpeed,
								  minRotSpeed, maxRotSpeed,
								  minAlpha, maxAlpha);
		sim.addSimulatable(pg);
	}

	sim.run();
}

bool loadDefaultTexture(sf::Texture &texture)
{
	Util::log(Util::LogLevel::Info, "No Image Specified!");
	if (!texture.loadFromFile(DEFAULT_IMAGE_PATH))
	{
		Util::log(Util::LogLevel::Error, "Default Image not loaded!");
		return false;
	};
	return true;
}

bool loadFileTexture(sf::Texture &texture, const char *path)
{
	if (!texture.loadFromFile(path))
	{
		Util::log(Util::LogLevel::Error, "Specified Image not loaded!");
		return false;
	};
	return true;
}

sf::Color getRandomColor()
{
	sf::Color color(rand() % 255, rand() % 255, rand() % 255);
	return color;
}