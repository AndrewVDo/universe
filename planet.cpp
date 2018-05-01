#include<cmath>
#include<stdio.h>
using namespace std;

class Planet {
private:
    double dx, dy;
    double x, y;
    double mass;
    double radius;

public:
    Planet();
    Planet(double xSpeed, double ySpeed, double xPos, double yPos, double planetMass, double planetRadius);
    void changePos(double xLoc, double yLoc);
    void changeVel(double xSpeed, double ySpeed);
    void changeMass(double planetMass);
    void changeRad(double planetRadius);
    double getPosX()const;
    double getPosY()const;
    double getVelX()const;
    double getVelY()const;
    double getMass()const;
    double getRad()const;
    void updateVel(Planet* p);
    void updatePos();
};

Planet::Planet(){
    this->dx = 0;
    this->dy = 0;
    this->x = 0;
    this->y = 0;
    this->mass = 1;
    this->radius = 1;
}
Planet::Planet(double xSpeed, double ySpeed, double xPos, double yPos, double planetMass, double planetRadius){
    this->dx = xSpeed;
    this->dy = ySpeed;
    this->x = xPos;
    this->y = yPos;
    this->mass = planetMass;
    this->radius = planetRadius;
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
void Planet::updateVel(Planet *p) {
	double xDist = (this->x) - (p->x);
	double yDist = (this->y) - (p->y);
	double distance2 = xDist * xDist + yDist * yDist;
	double direction;
	direction = atan2(yDist, xDist);
	//if(xDist < 0 && yDist < 0) direction = atan2(yDist, xDist);
	//else if(xDist > 0 && yDist < 0) direction = 1 - atan2(yDist, xDist);
	//else if(xDist < 0 && yDist > 0) direction = -atan2(yDist, xDist);
	//else direction = 1 + atan2(yDist, xDist);
	double accel = 0;
		if(distance2 > 1)accel = -6.67 * pow(10,-7) * p->getMass() / distance2;
	this->dx += cos(direction) * accel;
	this->dy += sin(direction) * accel;
    return;
}
void Planet::updatePos(){
    this->x += this->dx;
    this->y += this->dy;
    return;
}

