#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Universe;
class Celestial_Body;
class Planet;
class Asteroid;

class Universe {
private:
  float width, height,    // window dimensions
      scroll_x, scroll_y, // scroll value for viewing window
      zoom;               // zoom value for viewing window
  std::vector<Celestial_Body *>
      body_list; // array containing all celestial elements
  bool paused;   // pause simulation flag
public:
  Universe();                 // default constructor
  Universe(float w, float h); // create universe with dimensions
  ~Universe(); // destructor, deletes all objects associated with universe

  void change_dimension(float width, float height); // change window dimension

  float get_width() const;         // return width
  float get_height() const;        // return height
  float get_scroll_x() const;      // return x scroll value
  float get_scroll_y() const;      // return y scroll value
  float get_zoom() const;          // return zoom value
  Celestial_Body *get_body(int n); // retrieve pointer to n'th celestial entity
  int get_list_size(); // retrieve int number of celestial bodies in this
                       // universe

  void create_planet(
      float x, float y, float dx, float dy, float mass, float radius,
      sf::Color body_color); // create planet(circle) with various parameters
  void create_asteroid(float x, float y, float dx, float dy, float mass,
                       float radius,
                       sf::Color body_color); // create asteroid(triangle) with
                                              // various parameters
  void delete_body(int n);                    // delete n'th celestial body

  void update_universe(); // update all physics associated with the universe
  void combine_body(int i, int j); // combine the j'th entity with the i'th
                                   // entity, all mass and energy is conserved
  void render_universe();          // display physics calculations to screen
  void make_orbit(int i, int j,
                  bool clockwise); // make the i'th celestial body orbit the
                                   // j'th celestial body, clockwise or
                                   // counterclockwise can also be determined
};

class Celestial_Body {
protected:
  float x, y,       // XY Coordinates
      dx, dy,       // XY Velocity
      fx, fy,       // XY force, this value is cleared at the beginning of each
                    // calculation
      mass, radius; // mass and radius of planet/asteroid
  sf::Color body_color; // colour of celestial entity
  int polygon_sides; // number of sides to sfml drawing app, 3 for asteroid, 20
                     // for planet

public:
  Celestial_Body(); // default constructor
  Celestial_Body(
      float x, float y, float dx, float dy, float mass, float radius,
      sf::Color body_color); // create a celestial body with various parameters

  void change_position(float x, float y);   // change position of celestial body
  void change_velocity(float x, float y);   // change velocity of celestial body
  void change_mass(float mass);             // change mass of celestial body
  void change_radius(float radius);         // change radius of celestial body
  void change_color(sf::Color planetColor); // change colour of celestial body
  void change_polygon_sides(int n);         // change number of sides of object

  float get_position_x() const; // retrieve x coordinate of celestial body
  float get_position_y() const; // retrieve y coordinate of celestial body
  float get_velocity_x() const; // get x velocity of celestial body
  float get_velocity_y() const; // get y velocity of celestial body
  float get_mass() const;       // get mass of celestial body
  float get_radius() const;     // get radius of celestial body
  sf::Color get_color() const;  // get color of celestial body
  int get_polygon_sides() const;

  void clear_force(); // empty the force values of a celestial body, this must
                      // be done at the beginning of each iteration
  Celestial_Body *
  update_force(Celestial_Body *p); // calculate forces enacted on this body by
                                   // all the other celestial entities
  void update_velocity();          // update velocity due to forces
  void update_position();          // update position due to velocity
  void
  make_orbit(Celestial_Body *p,
             bool clockwise); // set the kinetic energy of this object such that
                              // it has a stable orbit around p (considering all
                              // other forces are insignificant)
};

class Planet : public Celestial_Body {
public:
  Planet(); // default constructor
  Planet(float x, float y, float dx, float dy, float mass, float radius,
         sf::Color body_color); // create 30 side planet with various parameters
};

class Asteroid : public Celestial_Body {
public:
  Asteroid(); // default constructor
  Asteroid(
      float x, float y, float dx, float dy, float mass, float radius,
      sf::Color body_color); // create a 3 side asteroid with various parameters
};