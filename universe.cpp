/*
	universe.cpp
	Author: Andrew Do
	Date: March 16th 2018
*/
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Universe;
class Celestial_Body;
class Planet;
class Asteroid;

/*Universe class consist of members which keep track of all values necessary to 
display graphics and keep track of all the celestial bodies which lie within it.*/
class Universe {
private:
	float width, height,									//window dimensions
		scroll_x, scroll_y,									//scroll value for viewing window
		zoom;												//zoom value for viewing window
    std::vector<Celestial_Body*> body_list;					//array containing all celestial elements
	bool paused;											//pause simulation flag
public:
    Universe();												//default constructor
    Universe(float w, float h);								//create universe with dimensions
	~Universe();											//destructor, deletes all objects associated with universe

	void change_dimension(float width, float height);		//change window dimension

    float get_width() const;								//return width
    float get_height() const;								//return height
	float get_scroll_x() const;								//return x scroll value
	float get_scroll_y() const;								//return y scroll value
	float get_zoom() const;									//return zoom value
	Celestial_Body* get_body(int n);						//retrieve pointer to n'th celestial entity
	int get_list_size();									//retrieve int number of celestial bodies in this universe

	void create_planet(float x, float y, float dx, float dy, float mass, float radius, sf::Color body_color);		//create planet(circle) with various parameters
	void create_asteroid(float x, float y, float dx, float dy, float mass, float radius, sf::Color body_color);		//create asteroid(triangle) with various parameters
    void delete_body(int n);								//delete n'th celestial body

    void update_universe();									//update all physics associated with the universe
	void combine_body(int i, int j);						//combine the j'th entity with the i'th entity, all mass and energy is conserved
	void render_universe();									//display physics calculations to screen
	void make_orbit(int i, int j, bool clockwise);			//make the i'th celestial body orbit the j'th celestial body, clockwise or counterclockwise can also be determined

};

/*Celestial_Body class consist of members which keep track of position, speed, force
size, mass color and number of sides of a single object*/
class Celestial_Body {
protected:
	float x, y,												//XY Coordinates
		dx, dy,												//XY Velocity
		fx, fy,												//XY force, this value is cleared at the beginning of each calculation
		mass, radius;										//mass and radius of planet/asteroid
	sf::Color body_color;									//colour of celestial entity
	int polygon_sides;										//number of sides to sfml drawing app, 3 for asteroid, 20 for planet

public:
	Celestial_Body();										//default constructor
	Celestial_Body(float x, float y, float dx, float dy, float mass, float radius, sf::Color body_color);		//create a celestial body with various parameters

	void change_position(float x, float y);					//change position of celestial body
	void change_velocity(float x, float y);					//change velocity of celestial body
	void change_mass(float mass);							//change mass of celestial body
	void change_radius(float radius);						//change radius of celestial body
	void change_color(sf::Color planetColor);				//change colour of celestial body
	void change_polygon_sides(int n);						//change number of sides of object

	float get_position_x()const;							//retrieve x coordinate of celestial body
	float get_position_y()const;							//retrieve y coordinate of celestial body
	float get_velocity_x()const;							//get x velocity of celestial body
	float get_velocity_y()const;							//get y velocity of celestial body
	float get_mass()const;									//get mass of celestial body
	float get_radius()const;								//get radius of celestial body
	sf::Color get_color()const;								//get color of celestial body
	int get_polygon_sides()const;

	void clear_force();										//empty the force values of a celestial body, this must be done at the beginning of each iteration
	Celestial_Body* update_force(Celestial_Body* p);		//calculate forces enacted on this body by all the other celestial entities
	void update_velocity();									//update velocity due to forces
	void update_position();									//update position due to velocity
	void make_orbit(Celestial_Body* p, bool clockwise);		//set the kinetic energy of this object such that it has a stable orbit around p (considering all other forces are insignificant)

};

/*Planet class is a derivative of Celestial_Body which contains a constructor that
produces a round object*/
class Planet : public Celestial_Body {
public:
	Planet();												//default constructor
	Planet(float x, float y, float dx, float dy, float mass, float radius, sf::Color body_color);				//create 30 side planet with various parameters
};

/*Asteroid class is a derivative of Celestial_Body which contains a constructor that
produces a triangular object*/
class Asteroid : public Celestial_Body {
public:
	Asteroid();												//default constructor
	Asteroid(float x, float y, float dx, float dy, float mass, float radius, sf::Color body_color);				//create a 3 side asteroid with various parameters
};




Universe::Universe()
{
	this->width = 600.0;
	this->height = 400.0;
	paused = false;
	scroll_x = 0;
	scroll_y = 0;
	zoom = 1.0;
}

Universe::Universe(float w, float h)
{
	this->width = w;
	this->height = h;
	paused = false;
	scroll_x = 0;
	scroll_y = 0;
	zoom = 1;
}

Universe::~Universe()
{
	for (unsigned int i = 0; i < body_list.size(); i++) delete_body(i);
}

void Universe::change_dimension(float w, float h)
{
    this->width = w;
	this->height = h;
	return;
}

float Universe::get_width()const
{
    return this->width;
}

float Universe::get_height()const
{
    return this->height;
}

float Universe::get_scroll_x() const 
{
	return this->scroll_x;
}

float Universe::get_scroll_y() const 
{
	return this->scroll_y;
}

float Universe::get_zoom() const 
{
	return this->zoom;
}

Celestial_Body* Universe::get_body(int n)
{
	if (n < this->body_list.size()) return this->body_list[n];
	else return NULL;
}

int Universe::get_list_size() 
{
	return int(this->body_list.size());
}

void Universe::create_planet(float x, float y, float dx, float dy, float mass, float radius, sf::Color body_color) 
{
	Planet* planet = new Planet(x, y, dx, dy, mass, radius, body_color);
    this->body_list.push_back(planet);
    return;
}

void Universe::create_asteroid(float x, float y, float dx, float dy, float mass, float radius, sf::Color body_color)
{
	Asteroid* asteroid = new Asteroid(x, y, dx, dy, mass, radius, body_color);
	this->body_list.push_back(asteroid);
	return;
}

void Universe::delete_body(int n) 
{
	delete this->body_list[n];
	this->body_list.erase(body_list.begin() + n);
	return;
}

/*update_universe method calculates the refreshes force value and calculates the force between
every pair of celestial entities, combining them if they are touching. 
It then refreshes velocity and position*/
void Universe::update_universe()
{
	for (int i = 0; i < this->body_list.size(); i++) 
	{
		this->body_list[i]->clear_force();
	}
	int i = 0, j = 0;
	while (i < this->body_list.size()) 
	{
		j = i;
		while (j < this->body_list.size())
		{
            if(i != j)
			{
				Celestial_Body* collide = this->body_list[i]->update_force(this->body_list[j]);
				if (collide != NULL) //if a collision occurs the forces are cleare and i and j are restarted
				{
					combine_body(i, j);
					for (int k = 0; k < this->body_list.size(); k++) this->body_list[k]->clear_force();
					i = 0;
					j = 0;
				}
            }
			j++;
        }
		i++;
    }
	for (int i = 0; i < this->body_list.size(); ++i)
	{
		this->body_list[i]->update_velocity();
		this->body_list[i]->update_position();
	}
	return;
}

/*combine_body method conserves mass, velocity and joins them at their center of gravity
and resizes the new celestial body according to the summed volume*/
void Universe::combine_body(int i, int j) 
{
	Celestial_Body* c = this->body_list[i];
	Celestial_Body* p = this->body_list[j];

	float x_momentum = p->get_mass()*p->get_velocity_x() + c->get_mass() * c->get_velocity_x();
	float y_momentum = p->get_mass()*p->get_velocity_y() + c->get_mass() * c->get_velocity_y();
	float x_position = p->get_mass()*p->get_position_x() + c->get_mass() * c->get_position_x();
	float y_position = p->get_mass()*p->get_position_y() + c->get_mass() * c->get_position_y();

	float total_mass = p->get_mass() + c->get_mass();
	float total_radius = sqrt(p->get_radius() * p->get_radius() + c->get_radius() * c->get_radius());

		c->change_position(x_position / total_mass, y_position / total_mass);
		c->change_velocity(x_momentum / total_mass, y_momentum / total_mass);
		c->change_radius(total_radius);
		c->change_mass(total_mass);

		//todo: cast to different type
		if (c->get_polygon_sides() < p->get_polygon_sides())
		{
			c->change_polygon_sides(p->get_polygon_sides());
		}

			delete_body(j);
			return;
}

/*render_universe method provides all sfml related functios, it draws the planets and asteroids
as well as provides the controls for the viewing window. It also calls the update universe method
to procedually generate the physics*/
void Universe::render_universe()
{
	sf::RenderWindow window(sf::VideoMode(int(this->width), int(this->height)), "universe");
	std::cout << "Welcome to Universe Physics Modeller!\nUse arrow keys for navigation and mouse wheel to zoom\nPress Enter/Return to create a new Planet\nPress Spacebar to pause/resume\n";

	while (window.isOpen()) 
	{
		sf::Event event;
		while (window.pollEvent(event)) 
		{
			//Close Button Clicked
			if (event.type == sf::Event::Closed)
				window.close();

			//Keyboard Key Pressed Input
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space) 
				{
					if (this->paused == false) 
					{
						this->paused = true;
						std::cout << "paused\n";
					}
					else if (this->paused == true) 
					{
						this->paused = false;
						std::cout << "resumed\n";
					}
				}
				else if (event.key.code == sf::Keyboard::Up)
					this->scroll_y += 10;
				else if (event.key.code == sf::Keyboard::Down)
					this->scroll_y -= 10;
				else if (event.key.code == sf::Keyboard::Left)
					this->scroll_x += 10;
				else if (event.key.code == sf::Keyboard::Right)
					this->scroll_x -= 10;

			}

			//Mouse Wheel Movement Input
			if (event.type == sf::Event::MouseWheelMoved)
			{
				if (event.mouseWheel.delta < 0) 
				{
					if (this->zoom > 0.09)
						this->zoom = this->zoom * 0.9;
				}
				else if (event.mouseWheel.delta > 0)
				{
					if (this->zoom < 10.0)
						this->zoom = this->zoom * 1.1;
				}

			}

		}

		window.clear(sf::Color::Black);

			if (paused == false)
				this->update_universe();

			//if (showAxis == true);

			for (int i = 0; i < this->get_list_size(); i++) 
			{
				sf::CircleShape body(this->body_list[i]->get_radius() * this->zoom, this->body_list[i]->get_polygon_sides());
				body.setFillColor(this->get_body(i)->get_color());
				body.setPosition( this->get_body(i)->get_position_x() * this->zoom + this->width / 2 - this->get_body(i)->get_radius() * this->zoom + this->scroll_x * this->zoom, -this->get_body(i)->get_position_y() * this->zoom + this->height / 2 - this->get_body(i)->get_radius() * this->zoom + this->scroll_y * this->zoom);
				window.draw(body);
			}

			window.display();

	}

	return;

}

/*make_orbit method makes the i'th planetary object orbit the j'th planetary object, this calculation
only works when all other objects around it apply insignifigant forces*/
void Universe::make_orbit(int i, int j, bool clockwise)
{
	this->body_list[i]->make_orbit(this->body_list[j], clockwise);
}





Celestial_Body::Celestial_Body() 
{
	this->x = 0;
	this->y = 0;
	this->dx = 0;
	this->dy = 0;
	this->fx = 0;
	this->fy = 0;
	this->mass = 1;
	this->radius = 1;
	this->body_color;
	this->polygon_sides = 4;
}

Celestial_Body::Celestial_Body(float x, float y, float dx, float dy, float mass, float radius, sf::Color body_color) 
{
	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;
	this->fx = 0;
	this->fy = 0;
	this->mass = mass;
	this->radius = radius;
	this->body_color = body_color;
	this->polygon_sides = 4;
}

void Celestial_Body::change_position(float x, float y) 
{
	this->x = x;
	this->y = y;
	return;
}

void Celestial_Body::change_velocity(float x, float y) 
{
	this->dx = x;
	this->dy = y;
	return;
}

void Celestial_Body::change_mass(float mass) 
{
	this->mass = mass;
	return;
}

void Celestial_Body::change_radius(float radius) 
{
	this->radius = radius;
	return;
}

void Celestial_Body::change_color(sf::Color planet_color) 
{
	this->body_color = planet_color;
	return;
}

void Celestial_Body::change_polygon_sides(int n)
{
	this->polygon_sides = n;
	return;
}

float Celestial_Body::get_position_x()const
{
	return this->x;
}

float Celestial_Body::get_position_y()const 
{
	return this->y;
}

float Celestial_Body::get_velocity_x()const 
{
	return this->dx;
}

float Celestial_Body::get_velocity_y()const 
{
	return this->dy;
}

float Celestial_Body::get_mass()const 
{
	return this->mass;
}

float Celestial_Body::get_radius()const
{
	return this->radius;
}

sf::Color Celestial_Body::get_color()const
{
	return this->body_color;
}

int Celestial_Body::get_polygon_sides()const
{
	return this->polygon_sides;
}

/*clear_force method refreshes all force values, this is necessary at the beginning of each update
to maintain simulation*/
void Celestial_Body::clear_force()
{
	this->fx = 0;
	this->fy = 0;
	return;
}

/*update_force calculates and applies the force to both this celestial object and it's neighbor*/
Celestial_Body* Celestial_Body::update_force(Celestial_Body *neighbor)
{
	float x_distance = this->x - neighbor->x;
	float y_distance = this->y - neighbor->y;
	float distance_squared = x_distance * x_distance + y_distance * y_distance;

	if (sqrt(distance_squared) < (this->radius + neighbor->radius)) return neighbor;
	else {
		float direction = atan2f(y_distance, x_distance);
		float force = -6.67 * pow(10, -11) * this->mass * neighbor->mass / distance_squared;
		this->fx += cos(direction) * force;
		this->fy += sin(direction) * force;
		neighbor->fx += cos(direction + 3.14159265359) * force;
		neighbor->fy += sin(direction + 3.14159265359) * force;
		return NULL;
	}
}

/*update_velocity method calculates the change in velocity due to the force and mass of this object
and updates it's value*/
void Celestial_Body::update_velocity()
{
	this->dx += this->fx / this->mass;
	this->dy += this->fy / this->mass;
	return;
}

/*update_position method calculates the distance travelled in one cycle and updates it's position*/
void Celestial_Body::update_position() 
{
	this->x += this->dx;
	this->y += this->dy;
	return;
}

/*make_orbit method sets the speed of this object sufficient enough to orbit p, clockwise determines 
which direction the oribt will occur*/
void Celestial_Body::make_orbit(Celestial_Body* p, bool clockwise)
{
	//v = sqrt(gm/r)
	float x_distance = this->x - p->x;
	float y_distance = this->y - p->y;
	float distance_squared = x_distance * x_distance + y_distance * y_distance;

	double velocity = sqrt(abs(-6.67 * pow(10, -11) * p->mass / sqrt(distance_squared)));
	float direction = atan2f(y_distance, x_distance);

	this->dx = abs(sin(direction) * velocity);
	this->dy = abs(cos(direction) * velocity);

	if (x_distance > 0 && y_distance > 0) 
	{
		if (clockwise) this->dy = -this->dy;
		else this->dx = -this->dx;
	}
	else if (x_distance < 0 && y_distance > 0)
	{
		if (!clockwise)
		{
			this->dx = -this->dx;
			this->dy = -this->dy;
		}
	}
	else if (x_distance < 0 && y_distance < 0)
	{
		if (clockwise) this->dx = -this->dx;
		else this->dy = -this->dy;
	}
	else if (x_distance > 0 && y_distance < 0)
	{
		if (clockwise)
		{
			this->dx = -this->dx;
			this->dy = -this->dy;
		}
	}

		return;

}

Planet::Planet() : Celestial_Body(0, 0, 0, 0, 1, 1, sf::Color::White) {}
Planet::Planet(float x, float y, float dx, float dy, float mass, float radius, sf::Color body_color) : Celestial_Body(x, y, dx, dy, mass, radius, body_color)
{
	this->polygon_sides = 30;
}

Asteroid::Asteroid() : Celestial_Body(0, 0, 0, 0, 1, 1, sf::Color::White) {}
Asteroid::Asteroid(float x, float y, float dx, float dy, float mass, float radius, sf::Color body_color) : Celestial_Body(x, y, dx, dy, mass, radius, body_color)
{
	this->polygon_sides = 3;
}