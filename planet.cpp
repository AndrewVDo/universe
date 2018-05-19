/*

	planet.cpp
	Author: Andrew Do
	This source file info related to a planet, it also contains methods that model
	gravitational interactions between two planet class objects

*/
#include<cmath>
#include<stdio.h>
#include <SFML/Graphics.hpp>
using namespace std;

class Planet {
private:
	double dx, dy;
	double x, y;
	double mass;
	double radius;
	sf::Color planetColor;

public:
	//Default Constructor for Planet, set mass and radius to 1.0, location and speed to 0.0
	Planet();
	//Non-Default Constructor for Planet, set (xSpeed, ySpeed, xPos, yPos, planetMass, planetRadius, planetColor)
	Planet(double xSpeed, double ySpeed, double xPos, double yPos, double planetMass, double planetRadius, sf::Color pColor);

	//Change position of Planet (xPos, yPos)
	void changePos(double xLoc, double yLoc);
	//Change Velocity of Planet (xSpeed, ySpeed)
	void changeVel(double xSpeed, double ySpeed);
	//ChangeMass of Planet
	void changeMass(double planetMass);
	//Change Radius of Planet
	void changeRad(double planetRadius);
	//Change Color of Planet
	void changeColor(sf::Color pColor);

	//Get X Position of planet
	double getPosX()const;
	//Get Y position of planet
	double getPosY()const;
	//get X velocity of planet
	double getVelX()const;
	//get Y velocity of planet
	double getVelY()const;
	//get mass of planet
	double getMass()const;
	//get radius of planet
	double getRad()const;
	//get color of planet
	sf::Color getColor()const;

	//apply gravitational acceleration and change velocity of planet
	Planet* updateVel(Planet* p);
	//update position of planet in accordance to acceleration
	void updatePos();

};

Planet::Planet(){

    this->dx = 0;
    this->dy = 0;
    this->x = 0;
    this->y = 0;
    this->mass = 1;
    this->radius = 1;
	this->planetColor;

}

Planet::Planet(double xSpeed, double ySpeed, double xPos, double yPos, double planetMass, double planetRadius, sf::Color pColor){

    this->dx = xSpeed;
    this->dy = ySpeed;
    this->x = xPos;
    this->y = yPos;
    this->mass = planetMass;
    this->radius = planetRadius;
	this->planetColor = pColor;

}

void Planet::changePos(double xPos, double yPos){

    this->x = xPos;
    this->y = yPos;

    return;

}

void Planet::changeVel(double xSpeed, double ySpeed){

    this->dx = xSpeed;
    this->dy = ySpeed;

    return;

}

void Planet::changeMass(double planetMass){

    this->mass = planetMass;

    return;

}

void Planet::changeRad(double planetRadius){

    this->radius = planetRadius;

    return;

}

void Planet::changeColor(sf::Color pColor) {

	this->planetColor = pColor;

	return;

}

double Planet::getPosX()const{

    return this->x;

}

double Planet::getPosY()const{

    return this->y;

}

double Planet::getVelX()const{

    return this->dx;

}

double Planet::getVelY()const{

    return this->dy;

}

double Planet::getMass()const{

    return this->mass;

}

double Planet::getRad()const{

    return this->radius;

}

sf::Color Planet::getColor()const {

	return this->planetColor;

}

///	This function calculates the acceleration between this current planet caused
/// by it's neighbor p and uodates this planet's current speed
Planet* Planet::updateVel(Planet *p) {

	double xDist = (this->x) - (p->x);
	double yDist = (this->y) - (p->y);
	double distance2 = xDist * xDist + yDist * yDist;

	if (sqrt(distance2) < (this->getRad() + p->getRad())) {
		return p;
	}
	else {
		double direction = atan2(yDist, xDist);
		double accel = 0;
		if (distance2 > 1)accel = -6.67 * pow(10, -11) * p->getMass() / distance2;
		this->dx += cos(direction) * accel;
		this->dy += sin(direction) * accel;
		return NULL;
	}

}

///	This function updates this current planet's position
/// according to it's speed
void Planet::updatePos(){

    this->x += this->dx;
    this->y += this->dy;

    return;

}


