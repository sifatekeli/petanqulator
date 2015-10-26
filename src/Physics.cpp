
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
    /*
    // met a jour la position
    for (int i=0; i<_spheres.Taille(); i++)
    {
        Vecteur3 & vitesse = _spheres[i]->Vitesse();
        _spheres[i]->Position() += vitesse * duree;
    }

    // met a jour la vitesse selon les collisions
    computeCollisions();

    // met a jour la vitesse selon les forces
    for (int i=0; i<_spheres.Taille(); i++)
    {
        ObjetSphere & sphere = *_spheres[i];

        // calcule toutes les forces
        Vecteur3 forces(0, 0, 0);
        for (int j=0; j<_forces.Taille(); j++)
        {
            forces += _forces[j]->computeForce(sphere);
        }

        // calcule l'acceleration
        Vecteur3 acceleration = forces / sphere.Masse();

        // met a jour la vitesse
        sphere.Vitesse() += acceleration * duree;
    }
    */
}

void Physics::computeCollisions()
{
    /*
    int nbSpheres = _spheres.Taille();

    // memorise si les spheres subissent deja une collision
    // (une collision par sphere)
    bool * subitCollision = new bool[nbSpheres];
    for (int i=0; i<nbSpheres; i++)
    {
        subitCollision[i] = false;
    }

    // calcule la collision la plus proche de chaque objet
    // et met a jour les vitesses et positions
    for (int i=0; i<nbSpheres; i++)
    {
        ObjetSphere & sphere1 = *_spheres[i];

        // trouve la collision la plus proche
        int k = 0;
        float distanceMin = 1;
        for (int j=i+1; j<nbSpheres; j++)
        {
            ObjetSphere & sphere2 = *_spheres[j];

            // calcule la distance entre les spheres
            Vecteur3 c1c2(sphere1.Position(), sphere2.Position());
            float distance = c1c2.Norme2() - sphere1.Rayon() - sphere2.Rayon();

            // retient la sphere la plus proche qui n'a pas deja subit une collision
            if (distance < distanceMin && !subitCollision[j])
            {
                k = j;
                distanceMin = distance;
            }
        }

        // calcule la distance au sol
        float distancePlan = sphere1.Position().Y() - sphere1.Rayon();

        // traite la collision la plus proche
        // considere les spheres et le sol
        if (distanceMin < distancePlan)
        {
            if (distanceMin < 0)	// collision avec une sphere
            {
                subitCollision[k] = true;
                computeCollision(sphere1, *_spheres[k]);
            }
        }
        else			// distanceMin > distancePlan
        {
            if (distancePlan < 0)	// collision avec le sol
            {
                computeCollision(sphere1, _plan);
            }
        }
    }

    delete [] subitCollision;
    */
}

void Physics::computeCollision(Ball & ball1, Ball & ball2) const
{
/*
    float m1 = sphere1.Masse();
    float m2 = sphere2.Masse();

    Vecteur3 p1 = sphere1.Position();
    Vecteur3 p2 = sphere2.Position(); 

    Vecteur3 v1 = sphere1.Vitesse(); 
    Vecteur3 v2 = sphere2.Vitesse(); 

    // vecteurs unitaires sur la ligne des centres des boules
    Vecteur3 u1(sphere1.Position(), sphere2.Position());
    u1.Normaliser();
    Vecteur3 u2 = -u1;

    // met a jour les vitesses
    // changement de repere des vecteurs vitesse
    Vecteur3 v1x = u1 * ProduitScalaire(v1, u1);
    Vecteur3 v1y = v1 - v1x;
    Vecteur3 v2x = u2 * ProduitScalaire(v2, u2);
    Vecteur3 v2y = v2 - v2x;

    // collision elastique de spheres
    sphere1.Vitesse() = v1y + v1x - ((v1x-v2x) / (1 + m1/m2)) * 2; 
    sphere2.Vitesse() = v2y + v2x - ((v2x-v1x) / (1 + m2/m1)) * 2; 

    // deplace la plus petite sphere pour stabiliser la scene
    float distance = sphere1.Rayon() + sphere2.Rayon();
    if (sphere1.Rayon() > sphere2.Rayon())
        sphere2.Position() = p1 + u1 * distance;
    else
        sphere1.Position() = p2 + u2 * distance;
    */
}

void Physics::computeCollision(Ball & ball, Ground & ground) const
{
    /*
    // empeche la sphere de traverser le sol
    sphere.Position().Y() = sphere.Rayon();

    // met a jour la vitesse
    sphere.Vitesse().Y() = - (sphere.Vitesse().Y() * plan.Amortissement());
    */
}

