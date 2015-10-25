#include "Force.hpp"

// ForceMilieu
float & ForceMilieu::Viscosite()
{
  return _viscosite;
}

Vecteur3 ForceMilieu::Calculer(Objet & objet)
{
  return -(objet.Vitesse() * _viscosite * objet.Volume());
}

// ForceGravite
Vecteur3 & ForceGravite::Gravite()
{
  return _gravite;
}

Vecteur3 ForceGravite::Calculer(Objet &)
{
  return _gravite;
}
