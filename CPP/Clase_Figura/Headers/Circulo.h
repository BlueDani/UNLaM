#ifndef CIRCULO_H_INCLUDED
#define CIRCULO_H_INCLUDED

#include "Figura2D.h"

#define PI 3.14159265358979323846

class Circulo : public Figura2D
{
private:
	//float *_radio; NO
	float _radio;

public:
    Circulo();
	Circulo(float r);
	//~Circulo();   NO

	virtual float area() const;
	virtual float perimetro() const;
};

#endif // CIRCULO_H_INCLUDED
