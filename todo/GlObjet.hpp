#ifndef INCLUDE_GLOBJET
#define INCLUDE_GLOBJET

#include "Objet.hpp"
#include "Vecteur3.hpp"
#include "Tireur.hpp"

// materiau OpenGL
class GlMaterial
{
 public:
  float _diffuse[4];
  float _specular[4];
  float _shininess[4];

  GlMaterial(void);
};

// un objet affichable comprend au moins un materiau et une fonction d'affichage
class GlObjet
{
  GlMaterial _material;

 public:
  virtual ~GlObjet() {}
  virtual void Afficher(void) = 0;

  GlMaterial & Material();
};

class GlObjetSphere : public GlObjet
{
  ObjetSphere & _objetSphere;

 public:
  GlObjetSphere(ObjetSphere & objetSphere);
  void Afficher(void);
};

class GlObjetPlan : public GlObjet
{
  ObjetPlan & _objetPlan;

 public:
  GlObjetPlan(ObjetPlan & objetPlan);
  void Afficher(void);
};

class GlObjetTireur : public GlObjet
{
  Tireur & _tireur;

 public:
  GlObjetTireur(Tireur & tireur);
  void Afficher(void);
};

#endif
