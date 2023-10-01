#ifndef TRIANGULO_H_INCLUDED
#define TRIANGULO_H_INCLUDED

#include "Figura2D.h"
#include "ConstruccionTrianguloException.h"

class Triangulo : public Figura2D
{
private:
    float _lado1;
    float _lado2;
    float _lado3;
    float _semiperimetro;

public:
    Triangulo();
    Triangulo(float l1, float l2, float l3);
	//~Triangulo();

	virtual float area() const;
	virtual float perimetro() const;
};


#endif // TRIANGULO_H_INCLUDED
