#include "universe.h"
#include "planet.h"
#include <iostream>
#include <iomanip>
#include <SFML/Window.hpp>

using namespace std;

void createDemo1() {

	universe* solar_system = new universe(1600, 900);

	solar_system->createPlanet(0, 0, 0, 0, 10000000000, 35, sf::Color::Yellow);
	solar_system->createPlanet(0, 0.0725, 150, 0, 10000000, 15, sf::Color::Green);
	solar_system->createPlanet(-0.001, 0.05, 300, 0, 50000000, 20, sf::Color::Blue);
	solar_system->createPlanet(-0.0005, 0.0625, 225, 0, 20000000, 17, sf::Color::Cyan);
	solar_system->createPlanet(0, 0.110, 60, 0, 200000, 1, sf::Color::White);
	solar_system->createPlanet(0, 0.110, 65, 0, 500000, 2.5, sf::Color::White);
	solar_system->createPlanet(0, 0.110, 70, 0, 800000, 4, sf::Color::White);
	solar_system->createPlanet(-0.01, 0.110, 60, 10, 500000, 2.5, sf::Color::Green);
	solar_system->createPlanet(-0.01, 0.110, 65, 10, 200000, 1, sf::Color::White);
	solar_system->createPlanet(-0.01, 0.110, 70, 10, 300000, 1.5, sf::Color::Red);
	solar_system->createPlanet(-0.02, 0.110, 65, 20, 500000, 2.5, sf::Color::Cyan);
	solar_system->createPlanet(-0.02, 0.110, 60, 20, 800000, 4, sf::Color::White);
	solar_system->createPlanet(-0.02, 0.110, 55, 20, 600000, 3, sf::Color::Blue);
	solar_system->createPlanet(0, -0.110, -60, 0, 300000, 1.5, sf::Color::White);
	solar_system->createPlanet(0, -0.110, -65, 0, 200000, 1, sf::Color::White);
	solar_system->createPlanet(0, -0.110, -70, 0, 100000, 0.5, sf::Color::Magenta);
	solar_system->createPlanet(0.01, -0.110, -60, -10, 600000, 3, sf::Color::White);
	solar_system->createPlanet(0.01, -0.110, -65, -10, 100000, 0.5, sf::Color::Yellow);
	solar_system->createPlanet(0.01, -0.110, -70, -10, 200000, 1, sf::Color::White);
	solar_system->createPlanet(0.02, -0.110, -65, -20, 300000, 1.5, sf::Color::Green);
	solar_system->createPlanet(0.02, -0.110, -60, -20, 400000, 2, sf::Color::White);
	solar_system->createPlanet(0.02, -0.110, -55, -20, 500000, 2.5, sf::Color::Red);

	for (int i = -500; i <= -300; i = i + 10) {
		solar_system->createPlanet(0.15, 0, i, -60, 500000, 2.5, sf::Color::Cyan);	//fix int entry
	}

	solar_system->renderUniverse();
	delete solar_system;

	return;

}

void createDemo2() {

	universe* solar_system = new universe(1600, 900);

	solar_system->createPlanet(0, 0, 0, 0, 500000000000, 50, sf::Color::Yellow);

	int xS, yS;

	for (int i = -500; i <= 500; i = i + 100) {
		for (int j = -500; j <= 500; j = j + 100) {
			if (i != 0) xS = -100 / i;
			if (j != 0) yS = -100 / j;
			solar_system->createPlanet(xS, yS, i, j, 10000, 5, sf::Color::Cyan);
		}
	}

	for (int i = -450; i <= 450; i = i + 100) {
		for (int j = -450; j <= 450; j = j + 100) {
			if (i != 0) xS = -100 / i;
			if (j != 0) yS = -100 / j;
			solar_system->createPlanet(xS, yS, i, j, 10000, 5, sf::Color::Blue);
		}
	}

	solar_system->renderUniverse();
	delete solar_system;

	return;

}


int main(void) {
	
	createDemo1();



	return 0;

}