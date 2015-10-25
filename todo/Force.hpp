#ifndef INCLUDE_FORCE
#define INCLUDE_FORCE

#include "Vecteur3.hpp"
#include "Objet.hpp"

// classe Force abstraite 
// ici, une force est un vecteur dépendant de la vitesse de l'objet
class Force
{
 public:
  Force() {}
  virtual ~Force() {}
  virtual Vecteur3 Calculer(Objet & objet) = 0;
};

// force exercee par le milieu ambiant sur l'objet
class ForceMilieu : public Force
{
  float _viscosite;

 public:
  float & Viscosite();
  Vecteur3 Calculer(Objet & objet);
};

// force de gravite exercee sur l'objet
class ForceGravite : public Force
{
 Vecteur3 _gravite;

 public:
  Vecteur3 & Gravite();
  Vecteur3 Calculer(Objet & objet);
};

#endif
