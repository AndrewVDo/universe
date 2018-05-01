#pragma once
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