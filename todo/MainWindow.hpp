#ifndef INCLUDE_MAINWINDOW
#define INCLUDE_MAINWINDOW

#include <QObject>
#include <QTime>

#include "MainForm.hpp"
#include "GlFrame.hpp"
#include "Objet.hpp"
#include "Calculateur.hpp"

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = 0);
  
 private:
  // sous fenetres
  MainForm _mainForm;
  GlFrame _glFrame;

  // marges pour la fenetre OpenGL
  const int _widthOffset;
  const int _heightOffset;

  // donnees pour la simulation
  Tireur _tireur;
  Calculateur _calculateur;
  QTime _time;
  float _dureeSimulation;

 protected:
  void resizeEvent(QResizeEvent *event);

public slots:
  // lance une boule et calcule la simulation
  void Tirer();

  // calcule la simulation
  void Simuler();

  // met a jour les donnees issues du formulaire
  void MajTireurTheta(double theta);
  void MajTireurPhi(double phi);
  void MajTireurVitesse(double vitesse);
};

#endif
