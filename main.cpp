#include "universe.h"
#include <iostream>
#include <iomanip>
#include <SFML/Window.hpp>
#include <cstdlib>

using namespace std;

void create_demo1()
{
	Universe* solar_system = new Universe(1600, 900);
	solar_system->create_planet(0, 0, 0, 0, 10000000000000, 50, sf::Color::Yellow);
	solar_system->create_planet(100, 0, 0, 0, 10000000, 5, sf::Color::Green);
	solar_system->create_planet(-200, 0, 0, 0, 20000000, 7, sf::Color::Cyan);
	solar_system->create_planet(-300, 0, 0, 0, 150000000, 13, sf::Color::Magenta);
	solar_system->create_planet(-400, 0, 0, 0, 80000000, 9, sf::Color::Red);
	solar_system->create_planet(500, 0, 0, 0, 150000000, 13, sf::Color::Blue);
	solar_system->create_planet(-600, 0, 0, 0, 100000000, 10, sf::Color::Cyan);

	for (int i = 1; i < 7; i++)
	{
		solar_system->make_orbit(i, 0, rand()%1);
	}

	for (int i = 7; i < 350; i++)
	{
		solar_system->create_asteroid(rand() % 1200 - 600, rand() % 1200 - 600, 0, 0, 100000, rand()%5, sf::Color::White); 
		solar_system->make_orbit(i, 0, 1);
	}

	//solar_system->create_planet(-1000, 300, 2.5, 0, 200000000000000, 50, sf::Color::Cyan);

	solar_system->render_universe();
	delete(solar_system);
}

int main(void)
{
	create_demo1();
	return 0;
}