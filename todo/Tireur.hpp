#ifndef INCLUDE_TIREUR
#define INCLUDE_TIREUR

#include "Vecteur3.hpp"

// Tireur
// definit la position, la vitesse et la direction initiales au lancement d'une boule
class Tireur
{
  float _theta, _phi, _vitesse;
  Vecteur3 _position;

 public:
  float & Theta();
  float & Phi();
  float & Vitesse();
  Vecteur3 & Position();
};

#endif
