#pragma once
#include <SFML/Graphics.hpp>
#include "../include/CelestialBody.h"
#include <vector>
#include <utility>

class Universe {
private:
  std::pair<float, float> display;
  std::pair<float, float> scroll;
  float zoom;              
  std::vector<CelestialBody *>body_list;
  bool paused;
public:
  Universe(float w, float h);
  ~Universe();

  void change_dimension(float width=600.0, float height=400.0);

  void create_planet(float x, float y, float dx, float dy, float mass, float radius,sf::Color bodyColor);
  void create_asteroid(float x, float y, float dx, float dy, float mass, float radius, sf::Color bodyColor);
  void delete_body(int n);      

  void update_universe();
  void combine_body(int i, int j);
                                  
  void render_universe();          
  void make_orbit(int i, int j, bool clockwise);
};