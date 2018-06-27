#include<cmath>
#include<stdio.h>
#include <SFML/Graphics.hpp>
#include <universe.h>
using namespace std;

class Celestial_Body {
protected:
	float x, y,
		dx, dy,
		fx, fy,
		mass, radius;
	sf::Color body_color;

public:
	Celestial_Body();
	Celestial_Body(float x, float y, float dx, float dy, float mass, float radius, sf::Color body_color);

	void change_position(float x, float y);
	void change_velocity(float x, float y);
	void change_mass(float mass);
	void change_radius(float radius);
	void change_color(sf::Color planetColor);

	float get_position_x()const;
	float get_position_y()const;
	float get_velocity_x()const;
	float get_velocity_y()const;
	float get_mass()const;
	float get_radius()const;
	sf::Color get_color()const;

	void clear_force();
	Celestial_Body* update_force(Celestial_Body* p);
	void update_velocity();
	void update_position();

};

class Planet : protected Celestial_Body {
public:
	Planet();
	Planet(float x, float y, float dx, float dy, float mass, float radius, sf::Color body_color);
	void draw_planet();

};

class Asteroid : protected Celestial_Body {
public:
	Asteroid();
	Asteroid(float x, float y, float dx, float dy, float mass, float radius, sf::Color body_color);
	void draw_asteroid();

};

Celestial_Body::Celestial_Body(){

    this->x = 0;
    this->y = 0;
    this->dx = 0;
    this->dy = 0;
	this->fx = 0;
	this->fy = 0;
    this->mass = 1;
    this->radius = 1;
	this->body_color;

}

Celestial_Body::Celestial_Body(float x, float y, float dx, float dy, float mass, float radius, sf::Color body_color) {

    this->x = x;
    this->y = y;
    this->dx = dx;
    this->dy = dy;
	this->fx = 0;
	this->fy = 0;
    this->mass = mass;
    this->radius = radius;
	this->body_color = body_color;

}

void Celestial_Body::change_position(float x, float y){

    this->x = x;
    this->y = y;
    return;

}

void Celestial_Body::change_velocity(float x, float y){

    this->dx = x;
    this->dy = y;
    return;

}

void Celestial_Body::change_mass(float mass){

    this->mass = mass;
    return;

}

void Celestial_Body::change_radius(float radius){

    this->radius = radius;
    return;

}

void Celestial_Body::change_color(sf::Color planet_color) {

	this->body_color = planet_color;
	return;

}

float Celestial_Body::get_position_x()const{

    return this->x;

}

float Celestial_Body::get_position_y()const{

    return this->y;

}

float Celestial_Body::get_velocity_x()const{

    return this->dx;

}

float Celestial_Body::get_velocity_y()const{

    return this->dy;

}

float Celestial_Body::get_mass()const{

    return this->mass;

}

float Celestial_Body::get_radius()const{

    return this->radius;

}

sf::Color Celestial_Body::get_color()const {

	return this->body_color;

}

void Celestial_Body::clear_force() {
	
	this->fx = 0;
	this->fy = 0;
	return;

}

Celestial_Body* Celestial_Body::update_force(Celestial_Body *neighbor) {

	float x_distance = this->x - neighbor->x;
	float y_distance = this->y - neighbor->y;
	float distance_squared = x_distance * x_distance + y_distance * y_distance;

	if ( sqrt( distance_squared ) < (this->radius + neighbor->radius) ) return neighbor;
	else {
		float direction = atan2f( y_distance, x_distance );
		float force = -6.67 * pow(10, -11) * this->mass * neighbor->mass / distance_squared;
		this->fy += sin(direction) * force;
		this->fy += cos(direction) * force;
		neighbor->fx += sin(direction + 3.14159265358979323846) * force;
		neighbor->fy += cos(direction + 3.14159265358979323846) * force;
		return NULL;
	}

}

void Celestial_Body::update_velocity() {

	this->dx = this->fx / this->mass;
	this->dy = this->fy / this->mass;
	return;

}

void Celestial_Body::update_position(){

    this->x += this->dx;
    this->y += this->dy;
    return;

}

