#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <utility>

struct CelestialBody {
  std::pair<float, float> pos;
  std::pair<float, float> vel;
  std::pair<float, float> force;   
  float mass;
  float radius; 
  sf::Color bodyColor; 
  int polySides; 

  CelestialBody(
    float x=0.0, 
    float y=0.0, 
    float dx=0.0,
    float dy=0.0,
    float mass=1.0, 
    float radius=1.0, 
    sf::Color bodyColor=sf::Color::White
  );

  void clear_force(); 
  bool update_force(
    CelestialBody &neighbor
  );

  void update_velocity();       
  void update_position();        
  void make_orbit(
    CelestialBody &p,
    bool clockwise
  ); 
};

class Planet : public CelestialBody {
public:
  Planet();
  Planet(float x, float y, float dx, float dy, float mass, float radius, sf::Color bodyColor); 
};

class Asteroid : public CelestialBody {
public:
  Asteroid();
  Asteroid(float x, float y, float dx, float dy, float mass, float radius, sf::Color bodyColor); 
};