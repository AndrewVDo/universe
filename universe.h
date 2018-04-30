#include<vector>
#include "planet.h"


class universe {
private:
	double width, height;
	//std::vector<Planet*> planetList;
public:
	universe();
	universe(double w, double h);
	~universe();
	void changeWidth(double w);
	void changeHeight(double h);
	double getWidth() const;
	double getHeight() const;
	void createPlanet(double xSpeed, double ySpeed, double xPos, double yPos, double planetMass, double planetRadius);
	void deletePlanet(int n);
	void updateUniverse();
	std::vector<Planet*> planetList;
};