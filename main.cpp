#include "universe.h"
#include <iostream>
#include <iomanip>
#include <SFML/Graphics.hpp>

using namespace std;

int main(void) {
		universe* solar_system = new universe(1000, 1000);

		solar_system->createPlanet(0, 0, 0, 0, 100, 1);
		solar_system->createPlanet(-0.0001, -0.0001, 5, 5, 1, 1);
		solar_system->createPlanet(-0.0001, -0.0001, 10, 10, 10, 1);

		for(int i = 0; i < 10000000; i++){
			solar_system->updateUniverse();
			double x0 = solar_system->planetList[0]->getPosX();
			double y0 = solar_system->planetList[0]->getPosY();

			double x1 = solar_system->planetList[1]->getPosX();
			double y1 = solar_system->planetList[1]->getPosY();

			double x2 = solar_system->planetList[2]->getPosX();
			double y2 = solar_system->planetList[2]->getPosY();

			cout << fixed << setprecision(1) << "P0-X: " << x0 << "\tY: " << y0 << "\t" << "//P1-X: " << x1 << "\tY:" << y1 << "\tP2-X: " << x2 << "\tY: " << y2 <<"\n";

		}

		delete solar_system;


		//TODO LIST
		/*
		1. create collision function
		2. have acceleration and collision play into one another
		3. create drawing functions
		*/
}