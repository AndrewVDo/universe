#include "universe.h"
#include "planet.h"
#include <iostream>
#include <iomanip>
#include <SFML/Window.hpp>

using namespace std;

int main(void) {
	


		universe* solar_system = new universe(1000, 1000);

		//Add planets to solar system here with format:

		solar_system->createPlanet(0, 0, 0, 0, 10000000000, 35, sf::Color::Yellow);
		solar_system->createPlanet(0, 0.0725, 150, 0, 10000000, 15, sf::Color::Green);
		solar_system->createPlanet(-0.001, 0.05, 300, 0, 50000000, 20, sf::Color::Blue);
		solar_system->createPlanet(-0.0005, 0.0625, 225, 0, 20000000, 17, sf::Color::Cyan);

		solar_system->createPlanet(0, 0.110, 60, 0, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(0, 0.110, 65, 0, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(0, 0.110, 70, 0, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(-0.01, 0.110, 60, 10, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(-0.01, 0.110, 65, 10, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(-0.01, 0.110, 70, 10, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(-0.02, 0.110, 65, 20, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(-0.02, 0.110, 60, 20, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(-0.02, 0.110, 55, 20, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(0, -0.110, -60, 0, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(0, -0.110, -65, 0, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(0, -0.110, -70, 0, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(0.01, -0.110, -60, -10, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(0.01, -0.110, -65, -10, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(0.01, -0.110, -70, -10, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(0.02, -0.110, -65, -20, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(0.02, -0.110, -60, -20, 100000, 2.5, sf::Color::White);
		solar_system->createPlanet(0.02, -0.110, -55, -20, 100000, 2.5, sf::Color::White);


		

	
		solar_system->renderUniverse();

		delete solar_system;

		return 0;

}