#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>

#include "MainWindow.hpp"


MainWindow::MainWindow(QWidget *parent) : 
  QMainWindow(parent), _mainForm(this, this),
  _glFrame(this, _calculateur.Plan(), _tireur),
  _widthOffset(200), _heightOffset(50)
{
  srand(time(0));

  // initialise le sol
  _calculateur.Plan().Amortissement() = 0.4f;
  _calculateur.Plan().XMin() = -6;
  _calculateur.Plan().XMax() = 6;
  _calculateur.Plan().ZMin() = -4;
  _calculateur.Plan().ZMax() = 4;
  _glFrame.GetGlObjetPlan().Material()._diffuse[0] = 0.4f;
  _glFrame.GetGlObjetPlan().Material()._diffuse[1] = 0.8f;
  _glFrame.GetGlObjetPlan().Material()._diffuse[2] = 0.4f;
  _glFrame.GetGlObjetPlan().Material()._specular[0] = 0.2f;

  _glFrame.GetGlObjetPlan().Material()._specular[1] = 0.4f;
  _glFrame.GetGlObjetPlan().Material()._specular[2] = 0.2f;

  // initialise les forces
  ForceGravite * forceGravite = new ForceGravite();
  _calculateur.AjouterForce(forceGravite);
  forceGravite->Gravite() = Vecteur3(0, -9.81f, 0);

  ForceMilieu * forceMilieu = new ForceMilieu();
  _calculateur.AjouterForce(forceMilieu);
  forceMilieu->Viscosite() = 20;

  // initialise le cochonnet
  ObjetSphere * cochonnet = new ObjetSphere();
  _calculateur.AjouterSphere(cochonnet);
  cochonnet->Rayon() = 0.1f;
  cochonnet->Masse() = 0.1f;
  cochonnet->Vitesse() = Vecteur3(0, 0, 0);

  float px = 4 * rand()/(float)RAND_MAX;
  float pz = 4 * rand()/(float)RAND_MAX;
  cochonnet->Position() = Vecteur3(px, 0.1f, pz);

  GlObjetSphere * glCochonnet = new GlObjetSphere(*cochonnet);
  _glFrame.AjouterSphere(glCochonnet);
  glCochonnet->Material()._diffuse[0] = 1;
  glCochonnet->Material()._diffuse[1] = 0.2f;
  glCochonnet->Material()._diffuse[2] = 0.2f;
  glCochonnet->Material()._specular[0] = 1;
  glCochonnet->Material()._specular[1] = 0.2f;
  glCochonnet->Material()._specular[2] = 0.2f;

  // tireur
  _tireur.Position() = Vecteur3(-6, 1, 0);
  _tireur.Theta() = 0;
  _tireur.Phi() = 0;
  _tireur.Vitesse() = 1;
  _glFrame.GetGlObjetTireur().Material()._diffuse[0] = 0.2f;
  _glFrame.GetGlObjetTireur().Material()._diffuse[1] = 0.2f;
  _glFrame.GetGlObjetTireur().Material()._diffuse[2] = 1;
  _glFrame.GetGlObjetTireur().Material()._specular[0] = 0.2f;
  _glFrame.GetGlObjetTireur().Material()._specular[1] = 0.2f;
  _glFrame.GetGlObjetTireur().Material()._specular[2] = 1;

  // connexion des signaux
  connect(_mainForm.pushButton_tirer, SIGNAL(clicked()), this, SLOT(Tirer()));
  connect(_mainForm.pushButton_simuler, SIGNAL(clicked()), this, SLOT(Simuler()));
  connect(_mainForm.doubleSpinBox_theta, SIGNAL(valueChanged(double)),
	  this, SLOT(MajTireurTheta(double)));
  connect(_mainForm.doubleSpinBox_phi, SIGNAL(valueChanged(double)),
	  this, SLOT(MajTireurPhi(double)));
  connect(_mainForm.doubleSpinBox_vitesse, SIGNAL(valueChanged(double)),
	  this, SLOT(MajTireurVitesse(double)));

  // autres parametres
  _dureeSimulation = 2;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
  _glFrame.resize(width() - _widthOffset, height() - _heightOffset);
}

void MainWindow::Simuler()
{
  // affiche un message d'attente dans la barre d'etat
  _mainForm.statusBar->showMessage("Simulation en cours...");

  // calcule la simulation sur la duree demandee 
  _time.restart();
  float dureeTotale = 0;	// duree totale effectuee
  while (dureeTotale < _dureeSimulation)
    {
      // calcule la simulation par pas de duree
      float duree = _time.restart() * 0.001;
      _calculateur.Maj(duree);
      _glFrame.repaint();
      dureeTotale += duree;
    }

  // vide la barre d'etat
  _mainForm.statusBar->clearMessage();
}

void MainWindow::Tirer()
{
  // cree la boule
  ObjetSphere * objetSphere = new ObjetSphere();
  _calculateur.AjouterSphere(objetSphere);
  objetSphere->Masse() = 1;
  objetSphere->Rayon() = 0.2f;
  objetSphere->Position() = _tireur.Position();

  // calcule le vecteur vitesse
  float theta = -_tireur.Theta()*M_PI/180.0;
  float phi = _tireur.Phi()*M_PI/180.0;
  float vx = cos(phi)*cos(theta);
  float vy = sin(phi);
  float vz = cos(phi)*sin(theta);
  objetSphere->Vitesse() = Vecteur3(vx, vy, vz) * _tireur.Vitesse();

  // met a jour l'affichage
  GlObjetSphere * glObjetSphere = new GlObjetSphere(*objetSphere);
  _glFrame.AjouterSphere(glObjetSphere);

  // calcule la simulation
  Simuler();
}

void MainWindow::MajTireurTheta(double theta)
{
  _tireur.Theta() = theta;
  _glFrame.update();
}

void MainWindow::MajTireurPhi(double phi)
{
  _tireur.Phi() = phi;
  _glFrame.update();
}

void MainWindow:: MajTireurVitesse(double vitesse)
{
  _tireur.Vitesse() = vitesse;
}

