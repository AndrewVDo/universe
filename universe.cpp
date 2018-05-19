/*

	universe.cpp
	Author: Andrew Do
	This source file exist to define the universe class which holds a list of planets, various variables that control the display screen
	as well as the functions that control interactions between planets and is responsible for updating the physics

*/
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "planet.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;

class universe {
private:
    double width, height;
    vector<Planet*> planetList;
	bool paused;
	bool showAxis;
	float scrollX, scrollY;
	float zoom;
	sf::RectangleShape xAxis;
	sf::RectangleShape yAxis;
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

//default constructor
universe::universe(){

    this->changeWidth(100.0);
    this->changeHeight(100.0);
	paused = false;
	showAxis = true;
	scrollX = 0;
	scrollY = 0;
	zoom = 1;

}

//universe constructor with parameters for width and height of window
universe::universe(double w, double h){

    this->changeWidth(w);
    this->changeHeight(h);
	paused = false;
	showAxis = true;
	scrollX = 0;
	scrollY = 0;
	zoom = 1;

}

//universe destructor
universe::~universe(){

	for (unsigned int i = 0; i < planetList.size(); i++) {
		deletePlanet(i);
	}

}

//change width of universe window
void universe::changeWidth(double w){

    this->width = w;

    return;

}

//change height of universe window
void universe::changeHeight(double h){

    this->height = h;

    return;

}

//get width of universe window
double universe::getWidth()const{

    return this->width;

}

//get hieght of universe window
double universe::getHeight()const{

    return this->height;

}

//return address of the n'th planet in the solar system
Planet* universe::getPlanet(int n) {

	if (n < this->planetList.size()) {

		return this->planetList[n];

	}

	return NULL;

}

//get number of planets in this universe
int universe::getListSize() {
	
	return int(this->planetList.size());

}

//create planet in this universe with parameters
void universe::createPlanet(double xSpeed, double ySpeed, double xPos, double yPos, double planetMass, double planetRadius, sf::Color pColor){

	Planet* planet = new Planet(xSpeed, ySpeed, xPos, yPos, planetMass, planetRadius, pColor);
    planetList.push_back(planet);

    return;

}

//delete n'th planet in solarsystem
void universe::deletePlanet(int n){

		delete planetList[n];
		planetList.erase(planetList.begin() + n);

	return;
}

//update velocity and position of all planets in this system as well as detect collosions
void universe::updateUniverse(){

	for (int i = 0; i < this->planetList.size(); ++i) {

		for(int j = 0; j < this->planetList.size(); j++) {

            if(i != j){

				Planet* collide = this->planetList[i]->updateVel(this->planetList[j]);

				if (collide != NULL) {
					combine(i, collide);
					if (j < i) i--;
				}

            }

        }

    }
	for (int i = 0; i < this->planetList.size(); ++i) {

		this->planetList[i]->updatePos();

	}

	return;

}

//combine 2 planets when collision occurs
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
		
		if (p->getRad() > c->getRad()) {
			c->changeColor(p->getColor());
		}

			deletePlanet(a);

			return;

}

//draw and update universe continuously
void universe::renderUniverse() {
	sf::RenderWindow window(sf::VideoMode(int(this->getWidth()), int(this->getHeight())), "universe");

	cout << "Welcome to Universe Physics Modeller!\nUse arrow keys for navigation and mouse wheel to zoom\nPress Enter/Return to create a new Planet\nPress Spacebar to pause/resume\n";

	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {

			//Close Button Clicked
			if (event.type == sf::Event::Closed)
				window.close();

			//Keyboard Key Pressed Input
			if (event.type == sf::Event::KeyPressed) {

				if (event.key.code == sf::Keyboard::Space) {

					if (this->paused == false) {
						this->paused = true;
						cout << "paused\n";
					}
					else if (this->paused == true) {
						this->paused = false;
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
				else if (event.key.code == sf::Keyboard::Return) {

					this->consoleCreatePlanet();

				}
				else if (event.key.code == sf::Keyboard::H) {
					
					if (this->showAxis == false) {
						this->showAxis = true;
					}
					else if (this->showAxis == true) {
						this->showAxis = false;
					}

				}

			}

			//Mouse Wheel Movement Input
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
			if (showAxis == true) {



			}

			for (int i = 0; i < this->getListSize(); i++) {

				sf::CircleShape planet(float(this->getPlanet(i)->getRad() * this->zoom), 30);
				planet.setFillColor(this->getPlanet(i)->getColor());
				planet.setPosition( float(this->getPlanet(i)->getPosX() * this->zoom + this->getWidth() / 2 - this->getPlanet(i)->getRad() * this->zoom + this->scrollX), float(-this->getPlanet(i)->getPosY() * this->zoom + this->getHeight() / 2 - this->getPlanet(i)->getRad() * this->zoom + this->scrollY));
				window.draw(planet);

			}

			window.display();

	}

	return;

}

//create a new planet from the console
void universe::consoleCreatePlanet() {

	double XSpeed, YSpeed, XPosition, YPosition, PlanetMass, PlanetRadius;
	enum Color {Black, Blue, Cyan, Green, Magenta, Red, White, Yellow };
	string PlanetColor;

	cout << "To create a planet, enter the following data in the same format\nXSpeed YSpeed XPosition YPosition PlanetMass PlanetRadius PlanetColor\n";
	cin >> XSpeed;
	cin >> YSpeed;
	cin >> XPosition;
	cin >> YPosition;
	cin >> PlanetMass;
	cin >> PlanetRadius;
	cin >> PlanetColor;

	if(PlanetColor == "Black")			this->createPlanet(XSpeed, YSpeed, XPosition, YPosition, PlanetMass, PlanetRadius, sf::Color::Black);
	else if (PlanetColor == "Blue")		this->createPlanet(XSpeed, YSpeed, XPosition, YPosition, PlanetMass, PlanetRadius, sf::Color::Blue);
	else if (PlanetColor == "Cyan")		this->createPlanet(XSpeed, YSpeed, XPosition, YPosition, PlanetMass, PlanetRadius, sf::Color::Cyan);
	else if (PlanetColor == "Green")	this->createPlanet(XSpeed, YSpeed, XPosition, YPosition, PlanetMass, PlanetRadius, sf::Color::Green);
	else if (PlanetColor == "Magenta")	this->createPlanet(XSpeed, YSpeed, XPosition, YPosition, PlanetMass, PlanetRadius, sf::Color::Magenta);
	else if (PlanetColor == "Red")		this->createPlanet(XSpeed, YSpeed, XPosition, YPosition, PlanetMass, PlanetRadius, sf::Color::Red);
	else if (PlanetColor == "White")	this->createPlanet(XSpeed, YSpeed, XPosition, YPosition, PlanetMass, PlanetRadius, sf::Color::White);
	else if (PlanetColor == "Yellow")	this->createPlanet(XSpeed, YSpeed, XPosition, YPosition, PlanetMass, PlanetRadius, sf::Color::Yellow);
	else {
		cout << "Wrong Color or incorrect Input\n";
		cin.ignore(1000, '\n');
		cin.clear();
	}
	
	return;

}


