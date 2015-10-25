#define _USE_MATH_DEFINES
#include <cmath>

#include <GL/glu.h>

#include "GlFrame.hpp"

GlFrame::GlFrame(QWidget *parent, ObjetPlan & objetPlan, Tireur & tireur) :
  QGLWidget(parent)
{
  // taille de la fenetre OpenGL
  setGeometry(190, 20, 441, 411);

  // lumiere
  _lightPosition[0] = 0;
  _lightPosition[1] = 1;
  _lightPosition[2] = 0;
  _lightPosition[3] = 0;

  // cree le tireur et le sol
  // et les ajoute dans l'ensemble d'objets pour automatiser l'affichage et la destruction
  _glObjetPlan = new GlObjetPlan(objetPlan);
  _glObjetTireur = new GlObjetTireur(tireur);
  _glObjets.Ajouter(_glObjetPlan);
  _glObjets.Ajouter(_glObjetTireur);

  // camera
  _theta = 0;
  _phi = 30;
  _motion = false;
  _motionCoef = -1;

    _clearColor.setRgb(0.8, 0.8, 0.0);
}

GlObjetTireur & GlFrame::GetGlObjetTireur()
{
  return *_glObjetTireur;
}

GlObjetPlan & GlFrame::GetGlObjetPlan()
{
  return *_glObjetPlan;
}

void GlFrame::initializeGL()
{

    /*
    qglClearColor(QColor(200, 200, 200));
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  */

    qglClearColor(_clearColor);
    //qglClearColor(QColor(200, 200, 200));
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}

void GlFrame::resizeGL(int w, int h)
{
  h = std::max<int>(h, 1);
  float ratio = w / (float)h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  gluPerspective(60, ratio, 1, 100);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 10.0, // position
	    0.0, 0.0, 0.0,  // center
	    0.0, 1.0, 0.0); // up vector

}

void GlFrame::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /*
  // place la camera
  glPushMatrix();
  glRotatef(_theta, 0, 1, 0);
  glRotatef(_phi, cos(M_PI*_theta/180.0), 0, sin(M_PI*_theta/180.0));

  // place la lumiere
  glLightfv(GL_LIGHT0, GL_POSITION, _lightPosition);

  //  affiche les spheres
  for (int i=0; i<_glObjets.Taille(); i++)
    {
      _glObjets[i]->Afficher();
    }

  glPopMatrix();
  */

}


void GlFrame::mousePressEvent(QMouseEvent *event)
{
  _xRef = event->pos().x();
  _yRef = event->pos().y();
  _thetaRef = _theta;
  _phiRef = _phi;
  _motion = true;
}

void GlFrame::mouseReleaseEvent(QMouseEvent *)
{
  _motion = false;
}

void GlFrame::mouseMoveEvent(QMouseEvent *event)
{
  if (_motion)
    {
      _theta = _thetaRef + _motionCoef*(_xRef - event->pos().x());
      _phi = _phiRef + _motionCoef*(_yRef - event->pos().y());
      update();
    }
}

void GlFrame::AjouterSphere(GlObjetSphere * glObjetsphere)
{
  _glObjets.Ajouter(glObjetsphere);
}

