#include "Circulo.h"

Circulo::Circulo()
{
    _radio = 0;
}

Circulo::Circulo(float r)
{
    if(r<0)
        throw MedidaNegativaException(1);

    _radio = r;
}

//Circulo::Circulo(float r) : _radio(r){}

float Circulo::area() const
{
    return PI*_radio*_radio;
}

float Circulo::perimetro() const
{
    return 2*PI*_radio;
}