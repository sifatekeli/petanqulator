#ifndef INCLUDE_CALCULATEUR
#define INCLUDE_CALCULATEUR

#include "Ensemble.hpp"
#include "Vecteur3.hpp"
#include "Objet.hpp"
#include "Force.hpp"

// Calculateur
// definit et calcule un modele physique sur une scene
// la scene comprend un plan (sol)
// la scene peut comprendre des boules et des forces
class Calculateur 
{
 public:
  // ajoute une boule ou une force
  void AjouterSphere(ObjetSphere * sphere);
  void AjouterForce(Force * force);

  // accede au plan de la scene
  ObjetPlan & Plan();

  // effectue la simulation : met a jour l'etat des spheres
  void Maj(float duree);

private:
  Ensemble<ObjetSphere> _spheres;
  Ensemble<Force> _forces;
  ObjetPlan _plan;

  // calcule toutes les collisions de la scene a l'instant courant
  void CalculerCollisions();

  // calcule la collision elastique de deux boules
  // ne verifie pas que les deux objets sont en contact
  void CalculerCollision(ObjetSphere & sphere1, ObjetSphere & sphere2) const;

  // calcule la collision d'une boule avec le sol
  // ne verifie pas que les deux objets sont en contact
  void CalculerCollision(ObjetSphere & sphere, ObjetPlan & plan) const;
};

#endif
