#include "include/universe.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <utility>

using namespace sf;
using namespace std;

Universe::Universe(float w, float h) {
  this->display = make_pair(w, h);
  this->scroll = make_pair(0, 0);
  paused = false;
  zoom = 1.0;
}

Universe::~Universe() {};

void Universe::create_planet(float x, float y, float dx, float dy, float mass,
                             float radius, Color bodyColor) {
  this->gbodyList.push_back(unique_ptr<CelestialBody>(new CelestialBody(x, y, dx, dy, mass, radius, bodyColor)));
  return;
}

void Universe::create_asteroid(float x, float y, float dx, float dy, float mass,
                               float radius, Color bodyColor) {
  this->gbodyList.push_back(unique_ptr<CelestialBody>(new CelestialBody(x, y, dx, dy, mass, radius, bodyColor)));
  return;
}

void Universe::update_universe() {
  for (int i = 0; i < this->gbodyList.size(); i++) {
    this->gbodyList[i]->clear_force();
  }
  int i = 0, j = 0;
  while (i < this->gbodyList.size()) {
    j = i;
    while (j < this->gbodyList.size()) {
      if (i != j) {
        if (this->gbodyList[i]->update_force(*this->gbodyList[j])) {
          combine_body(i, j);
          for (int k = 0; k < this->gbodyList.size(); k++)
            this->gbodyList[k]->clear_force();
          i = 0;
          j = 0;
        }
      }
      j++;
    }
    i++;
  }
  for (int i = 0; i < this->gbodyList.size(); ++i) {
    this->gbodyList[i]->update_velocity();
    this->gbodyList[i]->update_position();
  }
  return;
}

void Universe::combine_body(int i, int j) {
  float x_momentum =
      this->gbodyList[j]->mass * this->gbodyList[j]->vel.first + this->gbodyList[i]->mass * this->gbodyList[i]->vel.first;
  float y_momentum =
      this->gbodyList[j]->mass * this->gbodyList[j]->vel.second + this->gbodyList[i]->mass * this->gbodyList[i]->vel.second;
  float x_position =
      this->gbodyList[j]->mass * this->gbodyList[j]->pos.first + this->gbodyList[i]->mass * this->gbodyList[i]->pos.first;
  float y_position =
      this->gbodyList[j]->mass * this->gbodyList[j]->pos.second + this->gbodyList[i]->mass * this->gbodyList[i]->pos.second;

  float total_mass = this->gbodyList[j]->mass + this->gbodyList[i]->mass;
  float total_radius = sqrt(this->gbodyList[j]->radius * this->gbodyList[j]->radius + this->gbodyList[i]->radius * this->gbodyList[i]->radius);

  this->gbodyList[i]->pos.first = x_position / total_mass;
  this->gbodyList[i]->pos.second = y_position / total_mass;
  this->gbodyList[i]->vel.first = x_momentum / total_mass;
  this->gbodyList[i]->vel.second = y_momentum / total_mass;
  this->gbodyList[i]->radius = total_radius;
  this->gbodyList[i]->mass = total_mass;

  if (this->gbodyList[i]->polySides < this->gbodyList[j]->polySides) {
    this->gbodyList[i]->polySides = this->gbodyList[j]->polySides;
  }

  gbodyList.erase(gbodyList.begin() + j);
  return;
}

void Universe::render_universe() {
  RenderWindow window(VideoMode(int(this->display.first), int(this->display.second)),
                      "universe");
  cout << "Welcome to Universe Physics Modeller!\nUse arrow keys for "
          "navigation and mouse wheel to zoom\nPress Enter/Return to create a "
          "new Planet\nPress Spacebar to pause/resume\n";

  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      // Close Button Clicked
      if (event.type == Event::Closed)
        window.close();

      // Keyboard Key Pressed Input
      if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Space) {
          this->paused = !this->paused;
        } else if (event.key.code == Keyboard::Up)
          this->scroll.second += 10;
        else if (event.key.code == Keyboard::Down)
          this->scroll.second -= 10;
        else if (event.key.code == Keyboard::Left)
          this->scroll.first += 10;
        else if (event.key.code == Keyboard::Right)
          this->scroll.first -= 10;
      }

      // Mouse Wheel Movement Input
      if (event.type == Event::MouseWheelMoved) {
        if (event.mouseWheel.delta < 0) {
          if (this->zoom > 0.09)
            this->zoom = this->zoom * 0.9;
        } else if (event.mouseWheel.delta > 0) {
          if (this->zoom < 10.0)
            this->zoom = this->zoom * 1.1;
        }
      }
    }

    window.clear(Color::Black);

    if (paused == false){
      this->update_universe();
    }

    for (int i = 0; i < this->gbodyList.size(); i++) {
      CircleShape body(this->gbodyList[i]->radius * this->zoom,
                       this->gbodyList[i]->polySides);
      body.setFillColor(this->gbodyList[i]->bodyColor);
      body.setPosition(
          this->gbodyList[i]->pos.first * this->zoom + this->display.first / 2 -
              this->gbodyList[i]->radius * this->zoom +
              this->scroll.first * this->zoom,
          -this->gbodyList[i]->pos.second * this->zoom + this->display.second / 2 -
              this->gbodyList[i]->radius * this->zoom +
              this->scroll.second * this->zoom);
      window.draw(body);
    }

    window.display();
  }

  return;
}

void Universe::make_orbit(int i, int j, bool clockwise) {
  this->gbodyList[i]->make_orbit(*this->gbodyList[j], clockwise);
}