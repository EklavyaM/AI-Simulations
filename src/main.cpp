#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Util.h"
#include "Simulation.h"
#include "ParticleGenerator.h"

#define WIDTH 800
#define HEIGHT 600
#define DEFAULT_IMAGE_PATH "img/flare.png"

bool loadDefaultTexture(sf::Texture &texture);
bool loadFileTexture(sf::Texture &texture, const char *path);

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

	Simulation sim(WIDTH, HEIGHT, "Flock Simulation", 60);
	sim.addSimulatable(new ParticleGenerator(WIDTH, HEIGHT,
											 5000,
											 sf::Color::White,
											 testObjectTexture,
											 10));
	sim.run();

	return 0;
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
