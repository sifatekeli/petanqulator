
#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include "Utils.hpp"

enum player_t {PLAYER_RED, PLAYER_BLUE, PLAYER_JACK, PLAYER_NONE};

class Object 
{
    public:
        player_t _player;
        double _mass;
        vec3 _position;
        vec3 _velocity;

    private:
        // ugly data for ending simulations
        vec3 _delta;
        vec3 _oldDelta;
        vec3 _oldPosition;

    public:
        Object();
        Object(player_t player, double mass, vec3 position, vec3 velocity);
        ~Object();
        virtual double getVolume() const = 0;

        friend class Physics;
};

class Ball : public Object
{
    public:
        double _radius;

        Ball(player_t player, double mass, vec3 position, vec3 velocity, 
                double radius);
        double getVolume() const;
};

class Ground : public Object
{
    public:
        double _xMin;
        double _xMax;
        double _zMin;
        double _zMax;
        double _damping;

        Ground();
        Ground(player_t player, double mass, vec3 position, vec3 velocity, 
                double xMin, double xMax, double zMin, double zMax, 
                double damping);
        double getVolume() const;
};

#endif

