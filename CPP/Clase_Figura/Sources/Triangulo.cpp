#include "Triangulo.h"
#include <cmath>

Triangulo::Triangulo()
{
    _lado1 = 0;
    _lado2 = 0;
    _lado3 = 0;

    _semiperimetro = 0;
}

Triangulo::Triangulo(float l1, float l2, float l3)
{
    float suma;
    _lado1 = l1;
    _lado2 = l2;
    _lado3 = l3;

    if(l1<0 || l2<0 || l3<0)
        throw MedidaNegativaException(3);

    // Para poder construir un triángulo, la suma de la medida de dos de sus
    // lados debe ser mayor a la medida del tercer lado
    suma = _lado1 + _lado2;
    if(suma <= _lado3)
    {
        throw ConstruccionTrianguloException();
    }
    _semiperimetro = (_lado1+_lado2+_lado3)/2;
}

//Triangulo::~Triangulo()

float Triangulo::area() const
{
    return sqrt(_semiperimetro*(_semiperimetro-_lado1)*(_semiperimetro-_lado2)*(_semiperimetro-_lado3));
}

float Triangulo::perimetro() const
{
    return _lado1+_lado2+_lado3;
}
