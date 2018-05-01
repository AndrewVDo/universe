#include "universe.h"
#include "planet.h"
#include "draw.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main(void) {
	


		universe* solar_system = new universe(100, 100);

		solar_system->createPlanet(0, 0, 0, 0, 2000000, 25);
		solar_system->createPlanet(0, .05, 200, 0, 1000, 10);
		solar_system->createPlanet(0, .05, -300, 0, 2000, 10);
		solar_system->createPlanet(-.015, -.007, 400, 400, 100, 5);
		solar_system->createPlanet(.001, 0, -500, 100, 100, 5);

		drawScreen(1200, 780, solar_system);

		delete solar_system;


		//TODO LIST
		/*
		1. create collision function
		2. have acceleration and collision play into one another
		3. create drawing functions
		*/
}