
#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include "Utils.hpp"

class Object 
{
    public:
        int _player;
        float _mass;
        vec3 _position;
        vec3 _velocity;

    private:
        // ugly data for ending simulations
        vec3 _delta;
        vec3 _oldDelta;
        vec3 _oldPosition;

    public:
        Object();
        Object(int player, float mass, vec3 position, vec3 velocity);
        ~Object();
        virtual float getVolume() const = 0;

        friend class Physics;
};

class Ball : public Object
{
    public:
        float _radius;

        Ball(int player, float mass, vec3 position, vec3 velocity, 
                float radius);
        float getVolume() const;
};

class Ground : public Object
{
    public:
        float _xMin;
        float _xMax;
        float _zMin;
        float _zMax;
        float _damping;

        Ground();
        Ground(int player, float mass, vec3 position, vec3 velocity, 
                float xMin, float xMax, float zMin, float zMax, float damping);
        float getVolume() const;
};

#endif

