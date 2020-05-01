#pragma once
#include <SFML/Graphics.hpp>
#include "../include/CelestialBody.h"
#include <vector>
#include <utility>
#include <memory>

class Universe {
private:
  std::pair<float, float> display;
  std::pair<float, float> scroll;
  float zoom;              
  bool paused;
  std::vector< std::unique_ptr<CelestialBody> > gbodyList;
public:
  Universe(float w, float h);
  ~Universe();

  void create_planet(float x, float y, float dx, float dy, float mass, float radius,sf::Color bodyColor);
  void create_asteroid(float x, float y, float dx, float dy, float mass, float radius, sf::Color bodyColor);

  void update_universe();
  void combine_body(int i, int j);
                                  
  void render_universe();          
  void make_orbit(int i, int j, bool clockwise);
};