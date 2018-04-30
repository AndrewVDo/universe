#include<vector>
#include "planet.h"
using namespace std;

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
	vector<Planet*> planetList;
};

universe::universe(){
    this->changeWidth(100.0);
    this->changeHeight(100.0);
}
universe::universe(double w, double h){
    this->changeWidth(w);
    this->changeHeight(h);
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
void universe::createPlanet(double xSpeed, double ySpeed, double xPos, double yPos, double planetMass, double planetRadius){
	Planet* planet = new Planet(xSpeed, ySpeed, xPos, yPos, planetMass, planetRadius);
    planetList.push_back(planet);
    //draw?
    return;
}
void universe::deletePlanet(int n){
    delete planetList[n];
    //undraw?
}
void universe::updateUniverse(){
    for(int i = 0; i < this->planetList.size(); ++i){
		for(int j = 0; j < this->planetList.size(); j++) {
            if(i == j) continue;
            else{
                this->planetList[i]->updateVel(this->planetList[j]);
            }
        }
    }
	for (int i = 0; i < this->planetList.size(); ++i) {
		this->planetList[i]->updatePos();
	}
}


