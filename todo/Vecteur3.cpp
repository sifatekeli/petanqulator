#include "Vecteur3.hpp"

#include <cmath>

Vecteur3::Vecteur3(void) : _x(0), _y(0), _z(0)
{}

Vecteur3::Vecteur3(const Vecteur3 & v1, const Vecteur3 & v2) :
_x(v2._x - v1._x), _y(v2._y - v1._y), _z(v2._z - v1._z)
{}

Vecteur3::Vecteur3(float x, float y, float z) : _x(x), _y(y), _z(z)
{}

Vecteur3 & Vecteur3::operator=(const Vecteur3 &v)
{
  _x = v._x;
  _y = v._y;
  _z = v._z;
  return *this;
}

const float & Vecteur3::X() const 
{
  return _x;
}

const float & Vecteur3::Y() const 
{
  return _y;
}

const float & Vecteur3::Z() const 
{
  return _z;
}

float & Vecteur3::X()
{
  return _x;
}

float & Vecteur3::Y()
{
  return _y;
}

float & Vecteur3::Z()
{
  return _z;
}

Vecteur3 & Vecteur3::operator+=(const Vecteur3 &v)
{
  _x += v._x;
  _y += v._y;
  _z += v._z;
  return *this;
}

Vecteur3 & Vecteur3::operator/=(float k)
{
  _x /= k;
  _y /= k;
  _z /= k;
  return *this;
}

Vecteur3 Vecteur3::operator-()
{
  return Vecteur3(-_x, -_y, -_z);
}

Vecteur3 Vecteur3::operator*(float k) const
{
  return Vecteur3(k*_x, k*_y, k*_z);
}

Vecteur3 Vecteur3::operator/(float k) const
{
  return Vecteur3(_x/k, _y/k, _z/k);
}

float Vecteur3::Norme2Carree() const
{
  return _x*_x + _y*_y + _z*_z;
}

float Vecteur3::Norme2() const
{
  return sqrt(_x*_x + _y*_y + _z*_z);
}

Vecteur3 Vecteur3::operator+(const Vecteur3 &v) const
{
  return Vecteur3(_x+v._x, _y+v._y, _z+v._z);
}

Vecteur3 Vecteur3::operator-(const Vecteur3 &v) const
{
  return Vecteur3(_x-v._x, _y-v._y, _z-v._z);
}

void Vecteur3::Normaliser(void)
{
  float n = Norme2();
  if (n > 1e-6)
    {
      operator/=(n);
    }
}

float ProduitScalaire(const Vecteur3 &v1, const Vecteur3 &v2)
{
  return v1.X()*v2.X() + v1.Y()*v2.Y() + v1.Z()*v2.Z();
}
