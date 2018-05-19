#pragma once
#include <SFML/Graphics.hpp>

/*

	Planets are (currently) the sole object that occupies a universe class
	current implementation supports 2d physics as well as radius and color

*/
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