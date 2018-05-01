#include "planet.h"
#include "universe.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;

void drawScreen(unsigned int w, unsigned int h, universe* u);


void drawScreen(unsigned int w, unsigned int h, universe* u) {
	sf::RenderWindow window(sf::VideoMode(w,h), "universe");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		u->updateUniverse();
		for (int i = 0; i < u->planetList.size(); i++) {
			sf::CircleShape planet(float(u->planetList[i]->getRad()), 30);
			planet.setFillColor(sf::Color::White);
			planet.setPosition(float(u->planetList[i]->getPosX())+float(w/2), float(u->planetList[i]->getPosY()+float(h/2)));
			window.draw(planet);

		}
		

		window.display();
	}

}

//void drawTrail(Planet* p);