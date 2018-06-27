#pragma once
#include <SFML/Graphics.hpp>

/*

	Planets are (currently) the sole object that occupies a universe class
	current implementation supports 2d physics as well as radius and color

*/
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