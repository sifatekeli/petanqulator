#ifndef INCLUDE_VECTEUR3
#define INCLUDE_VECTEUR3

// vecteur dans R3
class Vecteur3
{
  float _x, _y, _z;

 public:
  // constructeurs
  Vecteur3(void);
  Vecteur3(const Vecteur3 & v1, const Vecteur3 & v2);
  Vecteur3(float x, float y, float z);

  // accesseurs
  const float & X() const;
  const float & Y() const;
  const float & Z() const;

  // modificateurs
  float & X();
  float & Y();
  float & Z();

  // operateurs
  Vecteur3 & operator=(const Vecteur3 &v);
  Vecteur3 & operator+=(const Vecteur3 &v);
  Vecteur3 & operator/=(float k);
  Vecteur3 operator-();
  Vecteur3 operator*(float k) const;
  Vecteur3 operator/(float k) const;
  Vecteur3 operator+(const Vecteur3 &v) const;
  Vecteur3 operator-(const Vecteur3 &v) const;

  // calculs sur la norme
  float Norme2Carree() const;
  float Norme2() const;
  void Normaliser(void);	// verifie que le vecteur n'est pas nul
};

float ProduitScalaire(const Vecteur3 &v1, const Vecteur3 &v2);

#endif

