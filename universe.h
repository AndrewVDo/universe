#pragma once
#include<vector>
#include "planet.h"


class universe {
private:
	double width, height;
	std::vector<Planet*> planetList;
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