
#include "Object.hpp"

Object::Object():
    _delta(1,1,1)
{}

Object::~Object()
{}

Object::Object(player_t player, double mass, vec3 position, vec3 velocity):
    _player(player), _mass(mass), _position(position), _velocity(velocity),
    _delta(1,1,1)
{}

Ball::Ball(player_t player, double mass, vec3 position, vec3 velocity, 
        double radius):
    Object(player, mass, position, velocity), _radius(radius)
{}

double Ball::getVolume() const
{
    return 4 * M_PI * _radius * _radius * _radius / 3.f;
}

Ground::Ground(): 
    Object()
{}

Ground::Ground(player_t player, double mass, vec3 position, vec3 velocity, 
        double xMin, double xMax, double zMin, double zMax, double damping):
    Object(player, mass, position, velocity),
    _xMin(xMin), _xMax(xMax), _zMin(zMin), _zMax(zMax), _damping(damping)
{}

double Ground::getVolume() const
{
    return INFINITY;
}
