#include "Objet.hpp"

// Objet
float & Objet::Masse()
{
  return _masse;
}

Vecteur3 & Objet::Position()
{
  return _position;
}

Vecteur3 & Objet::Vitesse()
{
  return _vitesse;
}

// ObjetSphere
float & ObjetSphere::Rayon()
{
  return _rayon;
}

float ObjetSphere::Volume()
{
  return 4 * M_PI * _rayon * _rayon * _rayon / 3.0;
}

// ObjetPlan
float & ObjetPlan::Amortissement()
{
  return _amortissement;
}

float & ObjetPlan::XMin()
{
  return _xMin;
}

float & ObjetPlan::XMax()
{
  return _xMax;
}

float & ObjetPlan::ZMin()
{
  return _zMin;
}

float & ObjetPlan::ZMax()
{
  return _zMax;
}

float ObjetPlan::Volume()
{
  return INFINI;
}

