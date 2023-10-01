#include "Cuadrado.h"

Cuadrado::Cuadrado()
{
    _lado = 0;
}

Cuadrado::Cuadrado(float l)
{
    if(l<0)
        throw MedidaNegativaException(2);

    _lado = l;
}

//Cuadrado::~Cuadrado()

float Cuadrado::area() const
{
    return _lado*_lado;
}

float Cuadrado::perimetro() const
{
    return 4*_lado;
}