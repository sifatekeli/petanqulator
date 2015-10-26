
#include "Physics.hpp"

void Physics::startSimulation()
{
    _isComputing = true;
}

bool Physics::isSimulationFinished()
{
    return _isComputing;
}

void Physics::computeSimulation(float duration)
{
    // met a jour la _position
    for (Ball & b : _balls)
        b._position += b._velocity * duration;

    // met a jour la vitesse selon les collisions
    computeCollisions();

    // met a jour la vitesse selon les forces
    for (Ball & b : _balls)
    {
        // calcule toutes les forces
        vec3 resultingForce = {0, 0, 0};
        for (const auto & uptrF : _uptrForces)
            resultingForce += uptrF->computeForce(b);

        // calcule l'acceleration
        vec3 acceleration = resultingForce / b._mass;

        // met a jour la vitesse
        b._velocity += acceleration * duration;
    }
}

void Physics::computeCollisions()
{
    unsigned nbBalls = _balls.size();

    // memorise si les spheres subissent deja une collision
    // (une collision par sphere)
    std::vector<bool> isColliding(nbBalls, false);

    // calcule la collision la plus proche de chaque objet
    // et met a jour les vitesses et positions
    for (unsigned i=0; i<nbBalls; i++)
    {
        Ball & ball1 = _balls[i];

        // trouve la collision la plus proche
        unsigned k = 0;
        float distanceMin = 1;
        for (unsigned j=i+1; j<nbBalls; j++)
        {
            Ball & ball2 = _balls[j];

            // calcule la distance entre les spheres
            vec3 c1c2 = ball2._position - ball1._position;
            float distance = c1c2.squaredNorm() - ball1._radius - ball2._radius;

            // retient la sphere la plus proche qui n'a pas deja subit une collision
            if (distance < distanceMin and not isColliding[j])
            {
                k = j;
                distanceMin = distance;
            }
        }

        // calcule la distance au sol
        float distanceToGround = ball1._position(1) - ball1._radius;

        // traite la collision la plus proche
        // considere les spheres et le sol
        if (distanceMin < distanceToGround)
        {
            // collision avec une sphere
            if (distanceMin < 0)
            {
                isColliding[k] = true;
                computeCollision(ball1, _balls[k]);
            }
        }
        // distanceMin > distanceToGround
        else
        {
            // collision avec le sol
            if (distanceToGround < 0)
            {
                computeCollision(ball1, _ground);
            }
        }
    }
}

void Physics::computeCollision(Ball & ball1, Ball & ball2) const
{
    float m1 = ball1._mass;
    float m2 = ball2._mass;

    vec3 p1 = ball1._position;
    vec3 p2 = ball2._position; 

    vec3 v1 = ball1._velocity; 
    vec3 v2 = ball2._velocity; 

    // vecteurs unitaires sur la ligne des centres des boules
    vec3 u1 = p2 - p1;
    u1.normalize();
    vec3 u2 = -u1;

    // met a jour les vitesses
    // changement de repere des vecteurs vitesse
    vec3 v1x = u1 * v1.dot(u1);
    vec3 v1y = v1 - v1x;
    vec3 v2x = u2 * v2.dot(u2);
    vec3 v2y = v2 - v2x;

    // collision elastique de spheres
    ball1._velocity = v1y + v1x - ((v1x-v2x) / (1 + m1/m2)) * 2; 
    ball2._velocity = v2y + v2x - ((v2x-v1x) / (1 + m2/m1)) * 2; 

    // deplace la plus petite sphere pour stabiliser la scene
    float distance = ball1._radius + ball2._radius;
    if (ball1._radius > ball2._radius)
        ball2._position = p1 + u1 * distance;
    else
        ball1._position = p2 + u2 * distance;
}

void Physics::computeCollision(Ball & ball, Ground & ground) const
{
    // empeche la sphere de traverser le sol
    ball._position(1) = ball._radius;

    // met a jour la vitesse
    ball._velocity(1) = - (ball._velocity(1) * ground._damping);
}

