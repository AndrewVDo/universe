#include "include/universe.h"
#include <SFML/Window.hpp>
#include <cstdlib>
#include <iomanip>
#include <iostream>

using namespace std;
using namespace sf;

void create_demo1() {
  Universe *solar_system = new Universe(1600, 900);
  solar_system->create_planet(0, 0, 0, 0, 10000000000000, 50, Color::Yellow);
  solar_system->create_planet(100, 0, 0, 0, 10000000, 5, Color::Green);
  solar_system->create_planet(-200, 0, 0, 0, 20000000, 7, Color::Cyan);
  solar_system->create_planet(-300, 0, 0, 0, 150000000, 13, Color::Magenta);
  solar_system->create_planet(-400, 0, 0, 0, 80000000, 9, Color::Red);
  solar_system->create_planet(500, 0, 0, 0, 150000000, 13, Color::Blue);
  solar_system->create_planet(-600, 0, 0, 0, 100000000, 10, Color::Cyan);

  for (int i = 1; i < 7; i++) {
    solar_system->make_orbit(i, 0, rand() % 1);
  }

  for (int i = 7; i < 350; i++) {
    solar_system->create_asteroid(rand() % 1200 - 600, rand() % 1200 - 600, 0,
                                  0, 100000, rand() % 5, Color::White);
    solar_system->make_orbit(i, 0, 1);
  }

  // solar_system->create_planet(-1000, 300, 2.5, 0, 200000000000000, 50,
  // Color::Cyan);

  solar_system->render_universe();
  delete (solar_system);
}

int main(void) {
  create_demo1();
  return 0;
}