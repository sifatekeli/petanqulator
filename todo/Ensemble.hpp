#ifndef INCLUDE_ENSEMBLE
#define INCLUDE_ENSEMBLE

#include <vector>

// ensemble d'elements dynamiques 
// permet d'ajouter un element, d'indexer un element et de connaitre la taille de l'ensemble
// les elements ajoutes doivent avoir ete cree par allocation dynamique
// a la destruction, la mémoire allouee pour les elements est liberee automatiquement
template<typename T>
class Ensemble {
  std::vector<T*> _elements;

 public:
  // destruction
  // libere automatiquement la memoire allouee pour les elements
  ~Ensemble(void) {
    for (unsigned int i=0; i<_elements.size(); i++)
      delete _elements[i];
  }

  // nombre d'elements de l'ensemble
  int Taille(void) const {
    return (int)_elements.size();
  }

  // ajoute un element dans l'ensemble
  // l'element doit avoir ete cree par allocation dynamique 
  void Ajouter(T* inElement) {
    _elements.push_back(inElement);
  }

  // retourne un pointeur vers l'element indexe
  // precondition : 0 <= inIndice < Taille()
  T* operator[](int inIndice) const {
    return _elements[inIndice];
  }
};

#endif

