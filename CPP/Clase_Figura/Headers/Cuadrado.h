#ifndef CUADRADO_H_INCLUDED
#define CUADRADO_H_INCLUDED

#include "Figura2D.h"

class Cuadrado : public Figura2D
{
private:
    float _lado;

public:
    Cuadrado();
    Cuadrado(float l);

	virtual float area() const;
	virtual float perimetro() const;
};


#endif // CUADRADO_H_INCLUDED
