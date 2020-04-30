/*
        universe.cpp
        Author: Andrew Do
        Date: March 16th 2018
*/
#include "include/universe.h"
#include "include/CelestialBody.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <utility>

using namespace sf;
using namespace std;

Universe::Universe(float w, float h) {
  this->display = make_pair(w, h);
  this->scroll = make_pair(0, 0);
  paused = false;
  zoom = 1.0;
}

Universe::~Universe() {
  for (unsigned int i = 0; i < body_list.size(); i++)
    delete_body(i);
}

void Universe::create_planet(float x, float y, float dx, float dy, float mass,
                             float radius, Color bodyColor) {
  Planet *planet = new Planet(x, y, dx, dy, mass, radius, bodyColor);
  this->body_list.push_back(planet);
  return;
}

void Universe::create_asteroid(float x, float y, float dx, float dy, float mass,
                               float radius, Color bodyColor) {
  Asteroid *asteroid = new Asteroid(x, y, dx, dy, mass, radius, bodyColor);
  this->body_list.push_back(asteroid);
  return;
}

void Universe::delete_body(int n) {
  delete this->body_list[n];
  this->body_list.erase(body_list.begin() + n);
  return;
}

void Universe::update_universe() {
  for (int i = 0; i < this->body_list.size(); i++) {
    this->body_list[i]->clear_force();
  }
  int i = 0, j = 0;
  while (i < this->body_list.size()) {
    j = i;
    while (j < this->body_list.size()) {
      if (i != j) {
        CelestialBody *collide =
            this->body_list[i]->update_force(this->body_list[j]);
        if (collide != NULL) 
        {
          combine_body(i, j);
          for (int k = 0; k < this->body_list.size(); k++)
            this->body_list[k]->clear_force();
          i = 0;
          j = 0;
        }
      }
      j++;
    }
    i++;
  }
  for (int i = 0; i < this->body_list.size(); ++i) {
    this->body_list[i]->update_velocity();
    this->body_list[i]->update_position();
  }
  return;
}

void Universe::combine_body(int i, int j) {
  CelestialBody *c = this->body_list[i];
  CelestialBody *p = this->body_list[j];

  float x_momentum =
      p->mass * p->vel.first + c->mass * c->vel.first;
  float y_momentum =
      p->mass * p->vel.second + c->mass * c->vel.second;
  float x_position =
      p->mass * p->pos.first + c->mass * c->pos.first;
  float y_position =
      p->mass * p->pos.second + c->mass * c->pos.second;

  float total_mass = p->mass + c->mass;
  float total_radius = sqrt(p->radius * p->radius + c->radius * c->radius);

  c->pos.first = x_position / total_mass;
  c->pos.second = y_position / total_mass;
  c->vel.first = x_momentum / total_mass;
  c->vel.second = y_momentum / total_mass;
  c->radius = total_radius;
  c->mass = total_mass;

  if (c->polySides < p->polySides) {
    c->polySides = p->polySides;
  }

  delete_body(j);
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
          if (this->paused == false) {
            this->paused = true;
            cout << "paused\n";
          } else if (this->paused == true) {
            this->paused = false;
            cout << "resumed\n";
          }
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

    if (paused == false)
      this->update_universe();

    // if (showAxis == true);

    for (int i = 0; i < this->body_list.size(); i++) {
      CircleShape body(this->body_list[i]->radius * this->zoom,
                       this->body_list[i]->polySides);
      body.setFillColor(this->body_list[i]->bodyColor);
      body.setPosition(
          this->body_list[i]->pos.first * this->zoom + this->display.first / 2 -
              this->body_list[i]->radius * this->zoom +
              this->scroll.first * this->zoom,
          -this->body_list[i]->pos.second * this->zoom + this->display.second / 2 -
              this->body_list[i]->radius * this->zoom +
              this->scroll.second * this->zoom);
      window.draw(body);
    }

    window.display();
  }

  return;
}

/*make_orbit method makes the i'th planetary object orbit the j'th planetary
object, this calculation only works when all other objects around it apply
insignifigant forces*/
void Universe::make_orbit(int i, int j, bool clockwise) {
  this->body_list[i]->make_orbit(this->body_list[j], clockwise);
}