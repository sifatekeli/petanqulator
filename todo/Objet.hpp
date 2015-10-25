#ifndef INCLUDE_OBJET
#define INCLUDE_OBJET

#include "Vecteur3.hpp"
#include "utils.hpp"

// Objet
// pour la simulation physique, un objet comprend au moins une masse, une position et une vitesse
class Objet
{
  float _masse;
  Vecteur3 _position;
  Vecteur3 _vitesse;

 public:
  virtual ~Objet() {}
  float & Masse();
  Vecteur3 & Position();
  Vecteur3 & Vitesse();

  virtual float Volume() = 0;
};

class ObjetSphere : public Objet
{
  float _rayon;

 public:
  float & Rayon();
  float Volume();
};

// plan (x, 0, z)
class ObjetPlan : public Objet
{
  // coefficient d'amortissement lors d'une collision avec une boule
  float _amortissement;	

  // limite du plan (au moins pour l'affichage)
  float _xMin, _xMax, _zMin, _zMax;

 public:
  float & Amortissement();
  float & XMin();
  float & XMax();
  float & ZMin();
  float & ZMax();

  float Volume();
};

#endif

