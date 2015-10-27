
#include "Object.hpp"

Object::Object():
    _delta(1,1,1)
{}

Object::~Object()
{}

Object::Object(int player, float mass, vec3 position, vec3 velocity):
    _player(player), _mass(mass), _position(position), _velocity(velocity),
    _delta(1,1,1)
{}

Ball::Ball(int player, float mass, vec3 position, vec3 velocity, float radius):
    Object(player, mass, position, velocity), _radius(radius)
{}

float Ball::getVolume() const
{
    return 4 * M_PI * _radius * _radius * _radius / 3.f;
}

Ground::Ground(): 
    Object()
{}

Ground::Ground(int player, float mass, vec3 position, vec3 velocity, 
        float xMin, float xMax, float zMin, float zMax, float damping):
    Object(player, mass, position, velocity),
    _xMin(xMin), _xMax(xMax), _zMin(zMin), _zMax(zMax), _damping(damping)
{}

float Ground::getVolume() const
{
    return INFINITY;
}
