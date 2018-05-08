#include<vector>
#include<stdlib.h>
#include "planet.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace std;

class universe {
private:
    double width, height;
    vector<Planet*> planetList;
	bool paused;
	float scrollX, scrollY;
	float zoom;
public:
    universe();
    universe(double w, double h);
	~universe();

    void changeWidth(double w);
    void changeHeight(double h);

    double getWidth() const;
    double getHeight() const;
	Planet* getPlanet(int n);
	int getListSize();

    void createPlanet(double xSpeed, double ySpeed, double xPos, double yPos, double planetMass, double planetRadius, sf::Color pColor);
    void deletePlanet(int n);
	void consoleCreatePlanet();

    void updateUniverse();
	void combine(int i, Planet* p);
	void renderUniverse();

};

universe::universe(){

    this->changeWidth(100.0);
    this->changeHeight(100.0);
	paused = false;
	scrollX = 0;
	scrollY = 0;
	zoom = 1;

}

universe::universe(double w, double h){

    this->changeWidth(w);
    this->changeHeight(h);
	paused = false;
	scrollX = 0;
	scrollY = 0;
	zoom = 1;

}

universe::~universe(){

	for (unsigned int i = 0; i < planetList.size(); i++) {
		deletePlanet(i);
	}

}

void universe::changeWidth(double w){

    this->width = w;

    return;

}

void universe::changeHeight(double h){

    this->height = h;

    return;

}

double universe::getWidth()const{

    return this->width;

}

double universe::getHeight()const{

    return this->height;

}

Planet* universe::getPlanet(int n) {

	if (n < this->planetList.size()) {
		return this->planetList[n];
	}
	return NULL;

}

int universe::getListSize() {
	
	return int(this->planetList.size());

}

void universe::createPlanet(double xSpeed, double ySpeed, double xPos, double yPos, double planetMass, double planetRadius, sf::Color pColor){

	Planet* planet = new Planet(xSpeed, ySpeed, xPos, yPos, planetMass, planetRadius, pColor);
    planetList.push_back(planet);

    return;

}

void universe::deletePlanet(int n){

    delete planetList[n];
	planetList.erase(planetList.begin() + n);

	return;
}

void universe::updateUniverse(){

	for (int i = 0; i < this->planetList.size(); ++i) {

		for(int j = 0; j < this->planetList.size(); j++) {

            if(i != j){

				Planet* collide = this->planetList[i]->updateVel(this->planetList[j]);

				if (collide != NULL) {
					combine(i, collide);
				}

            }

        }

    }
	for (int i = 0; i < this->planetList.size(); ++i) {

		this->planetList[i]->updatePos();

	}

	return;

}

void universe::combine(int i, Planet* p) {

	int a = 0;
	while (this->planetList[a] != p) a++;

	Planet* c = this->planetList[i];

	double xMomentum = p->getMass()*p->getVelX() + c->getMass() * c->getVelX();
	double yMomentum = p->getMass()*p->getVelY() + c->getMass() * c->getVelY();

	double xPos = p->getMass()*p->getPosX() + c->getMass() * c->getPosX();
	double yPos = p->getMass()*p->getPosY() + c->getMass() * c->getPosY();

	double totalMass = p->getMass() + c->getMass();
	double totalRad = sqrt(p->getRad() * p->getRad() + c->getRad() * c->getRad());

		c->changePos(xPos / totalMass, yPos / totalMass);
		c->changeVel(xMomentum / totalMass, yMomentum / totalMass);
		c->changeRad(totalRad);
		c->changeMass(totalMass);

			deletePlanet(a);

			return;

}

void universe::renderUniverse() {
	sf::RenderWindow window(sf::VideoMode(int(this->getWidth()), int(this->getHeight())), "universe");

	cout << "Welcome to Universe Physics Modeller!\nUse arrow keys for navigation and mouse wheel to zoom\n";

	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {

				if (event.key.code == sf::Keyboard::Space) {

					if (paused == false) {
						paused = true;
						cout << "paused\n";
					}
					else if (paused == true) {
						paused = false;
						cout << "resumed\n";
					}
				}
				else if (event.key.code == sf::Keyboard::Up) {

					this->scrollY += 15;

				}
				else if (event.key.code == sf::Keyboard::Down) {

					this->scrollY -= 15;

				}
				else if (event.key.code == sf::Keyboard::Left) {

					this->scrollX += 15;

				}
				else if (event.key.code == sf::Keyboard::Right) {

					this->scrollX -= 15;

				}

			}

			if (event.type == sf::Event::MouseWheelMoved)
			{
				if (event.mouseWheel.delta < 0) {

					if (this->zoom > 0.09)
						this->zoom = float(this->zoom * 0.9);

				}
				else if (event.mouseWheel.delta > 0) {

					if (this->zoom < 10.0)
						this->zoom = float(this->zoom * 1.1);

				}
			}

		}

			window.clear(sf::Color::Black);
			if (paused == false) {

				this->updateUniverse();

			}

			for (int i = 0; i < this->getListSize(); i++) {

				sf::CircleShape planet(float(this->getPlanet(i)->getRad() * this->zoom), 30);
				planet.setFillColor(this->getPlanet(i)->getColor());
				planet.setPosition( float(this->getPlanet(i)->getPosX() * this->zoom + this->getWidth() / 2 - this->getPlanet(i)->getRad() * this->zoom + this->scrollX),
					float(-this->getPlanet(i)->getPosY() * this->zoom + this->getHeight() / 2 - this->getPlanet(i)->getRad() * this->zoom + this->scrollY));
				window.draw(planet);
			}
			window.display();

	}
	return;
}

void universe::consoleCreatePlanet() {

	double XSpeed, YSpeed, XPosition, YPosition, PlanetMass, PlanetRadius;
	sf::Color PlanetColor;
	

	cout << "To create a planet, enter the following data in the same format\nXSpeed YSpeed XPosition YPosition PlanetMass PlanetRadius PlanetColor";
	cin >> XSpeed;
	cin >> YSpeed;
	cin >> XPosition;
	cin >> YPosition;
	cin >> PlanetMass;
	cin >> PlanetRadius;
	//cin >> PlanetColor;

	//this->createPlanet(XSpeed, YSpeed, XPosition, YPosition, PlanetMass, PlanetRadius, PlanetColor)

	

}


