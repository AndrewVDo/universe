#include "include/CelestialBody.h"
#include <cmath>

using namespace sf;
using namespace std;

CelestialBody::CelestialBody(float x, float y, float dx, float dy, float mass,
                               float radius, Color bodyColor) {
  this->pos = make_pair(x, y);
  this->vel = make_pair(dx, dy);
  this->force = make_pair(0, 0);
  this->mass = mass;
  this->radius = radius;
  this->bodyColor = bodyColor;
  this->polySides = 4;
}

void CelestialBody::clear_force() {
  this->force.first = 0;
  this->force.second = 0;
  return;
}

CelestialBody *CelestialBody::update_force(CelestialBody *neighbor) {
  float x_distance = this->pos.first - neighbor->pos.first;
  float y_distance = this->pos.second - neighbor->pos.second;
  float distance_squared = x_distance * x_distance + y_distance * y_distance;

  if (sqrt(distance_squared) < (this->radius + neighbor->radius)) {
    return neighbor;
  }
  float direction = atan2f(y_distance, x_distance);
  float force = -6.67 * pow(10, -11) * this->mass * neighbor->mass / distance_squared;
  this->force.first += cos(direction) * force;
  this->force.second += sin(direction) * force;
  neighbor->force.first += cos(direction + 3.14159265359) * force;
  neighbor->force.second += sin(direction + 3.14159265359) * force;
  return NULL;
}

void CelestialBody::update_velocity() {
  this->vel.first += this->force.first / this->mass;
  this->vel.second += this->force.second / this->mass;
  return;
}

void CelestialBody::update_position() {
  this->pos.first += this->vel.first;
  this->pos.second += this->vel.second;
  return;
}

void CelestialBody::make_orbit(CelestialBody *p, bool clockwise) {
  float x_distance = this->pos.first - p->pos.first;
  float y_distance = this->pos.second - p->pos.second;
  float distance_squared = x_distance * x_distance + y_distance * y_distance;

  double velocity = sqrt(abs(-6.67 * pow(10, -11) * p->mass / sqrt(distance_squared)));
  float direction = atan2f(y_distance, x_distance);

  this->vel.first = abs(sin(direction) * velocity);
  this->vel.second = abs(cos(direction) * velocity);

  if (x_distance > 0 && y_distance > 0) {
    if (clockwise){
      this->vel.second = -this->vel.second;
    }
    else {
      this->vel.first = -this->vel.first;
    }
  } else if (x_distance < 0 && y_distance > 0) {
    if (!clockwise) {
      this->vel.first = -this->vel.first;
      this->vel.second = -this->vel.second;
    }
  } else if (x_distance < 0 && y_distance < 0) {
    if (clockwise)
      this->vel.first = -this->vel.first;
    else
      this->vel.second = -this->vel.second;
  } else if (x_distance > 0 && y_distance < 0) {
    if (clockwise) {
      this->vel.first = -this->vel.first;
      this->vel.second = -this->vel.second;
    }
  }

  return;
}

Planet::Planet() : CelestialBody(0, 0, 0, 0, 1, 1, Color::White) {}
Planet::Planet(float x, float y, float dx, float dy, float mass, float radius, Color bodyColor)
    : CelestialBody(x, y, dx, dy, mass, radius, bodyColor) {
  this->polySides = 30;
}

Asteroid::Asteroid() : CelestialBody(0, 0, 0, 0, 1, 1, Color::White) {}
Asteroid::Asteroid(float x, float y, float dx, float dy, float mass, float radius, Color bodyColor)
    : CelestialBody(x, y, dx, dy, mass, radius, bodyColor) {
  this->polySides = 3;
}