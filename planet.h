#pragma once
#include <SFML/Graphics.hpp>

/**

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
	///Default Constructor for Planet, set mass and radius to 1.0, location and speed to 0.0
	Planet();
	///Non-Default Constructor for Planet, set (xSpeed, ySpeed, xPos, yPos, planetMass, planetRadius, planetColor)
	Planet(double xSpeed, double ySpeed, double xPos, double yPos, double planetMass, double planetRadius, sf::Color pColor);

	///Change position of Planet (xPos, yPos)
	void changePos(double xLoc, double yLoc);
	///Change Velocity of Planet (xSpeed, ySpeed)
	void changeVel(double xSpeed, double ySpeed);
	///ChangeMass of Planet
	void changeMass(double planetMass);
	///Change Radius of Planet
	void changeRad(double planetRadius);
	///Change Color of Planet
	void changeColor(sf::Color pColor);

	double getPosX()const;
	double getPosY()const;
	double getVelX()const;
	double getVelY()const;
	double getMass()const;
	double getRad()const;
	sf::Color getColor()const;

	Planet* updateVel(Planet* p);
	void updatePos();

};