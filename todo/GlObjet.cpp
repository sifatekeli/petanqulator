#include <QGLWidget>
#include <cmath>

#include <GL/glu.h>

#include "GlObjet.hpp"

GlMaterial::GlMaterial(void)
{
  _diffuse[0] = 0.8f;
  _diffuse[1] = 0.8f;
  _diffuse[2] = 0.8f;
  _diffuse[3] = 1.0f;

  _specular[0] = 0.8f;
  _specular[1] = 0.8f;
  _specular[2] = 0.8f;
  _specular[3] = 1.0f;

  _shininess[0] = 50;
  _shininess[1] = 50;
  _shininess[2] = 50;
  _shininess[3] = 1.0f;
}

GlMaterial & GlObjet::Material()
{
  return _material;
}

GlObjetSphere::GlObjetSphere(ObjetSphere & objetSphere) : 
  _objetSphere(objetSphere)
{}

void GlObjetSphere::Afficher(void)
{
  glPushMatrix();
  glTranslatef(_objetSphere.Position().X(), _objetSphere.Position().Y(),
	       _objetSphere.Position().Z());
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Material()._diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Material()._specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, Material()._shininess);
  gluSphere(gluNewQuadric(), _objetSphere.Rayon(), 32, 32);
  glPopMatrix();
}

GlObjetPlan::GlObjetPlan(ObjetPlan & objetPlan) : 
  _objetPlan(objetPlan)
{}

void GlObjetPlan::Afficher(void)
{
  glPushMatrix();
  glTranslatef(_objetPlan.Position().X(), _objetPlan.Position().Y(), 
	       _objetPlan.Position().Z());
  glMaterialfv(GL_FRONT, GL_DIFFUSE, Material()._diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, Material()._specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, Material()._shininess);
  glBegin(GL_QUADS);
  glNormal3f(0, 1, 0);
  glVertex3f(_objetPlan.XMin(), 0, _objetPlan.ZMin());
  glVertex3f(_objetPlan.XMin(), 0, _objetPlan.ZMax());
  glVertex3f(_objetPlan.XMax(), 0, _objetPlan.ZMax());
  glVertex3f(_objetPlan.XMax(), 0, _objetPlan.ZMin());
  glEnd();
  glPopMatrix();
}

GlObjetTireur::GlObjetTireur(Tireur & tireur) :
  _tireur(tireur)
{}

void GlObjetTireur::Afficher(void)
{
  glMaterialfv(GL_FRONT, GL_DIFFUSE, Material()._diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, Material()._specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, Material()._shininess);

  glPushMatrix();

  glTranslatef(_tireur.Position().X(), 
	       _tireur.Position().Y(), 
	       _tireur.Position().Z());
  glRotatef(90 + _tireur.Theta(), 0, 1, 0);
  glRotatef(-_tireur.Phi(), 1, 0, 0);

  gluCylinder(gluNewQuadric(), 0.06, 0.06, 1, 16, 2);
  glTranslatef(0, 0, 1);
  gluCylinder(gluNewQuadric(), 0.12, 0, 0.3, 16, 2);

  glPopMatrix();
}

