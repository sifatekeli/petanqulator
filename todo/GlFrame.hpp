#ifndef INCLUDE_GLFRAME
#define INCLUDE_GLFRAME

#include <QGLWidget>
#include <QMouseEvent>

#include "GlObjet.hpp"
#include "Ensemble.hpp"

// fenetre OpenGL affichant la scene simulee
// la scene comporte un tireur et un plan
// la scene peut comporter des boules
class GlFrame : public QGLWidget
{
    //Q_OBJECT
    QColor _clearColor;

 public:
  GlFrame(QWidget *parent, ObjetPlan & objetPlan, Tireur & tireur);

  // ajoute une boule
  void AjouterSphere(GlObjetSphere * glObjetSphere);

  // accede au tireur ou au plan
  GlObjetTireur & GetGlObjetTireur();
  GlObjetPlan & GetGlObjetPlan();
  
 protected:
  // fonction pour OpenGL sous Qt
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

  // gestion de la souris
  void mousePressEvent(QMouseEvent *event); 
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

 private:
  // lumiere
  float _lightPosition[4];

  // camera
  int _xRef;
  int _yRef;
  float _theta;
  float _phi;
  float _thetaRef;
  float _phiRef;
  bool _motion;
  float _motionCoef;

  // objets a afficher
  Ensemble<GlObjet> _glObjets;
  GlObjetPlan * _glObjetPlan;
  GlObjetTireur * _glObjetTireur;
};

#endif
