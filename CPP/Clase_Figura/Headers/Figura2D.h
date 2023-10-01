#ifndef FIGURA2D_H_INCLUDED
#define FIGURA2D_H_INCLUDED

#include "MedidaNegativaException.h"

class Figura2D
{

public:
    Figura2D();
    virtual ~Figura2D();

    virtual float area() const = 0;
    virtual float perimetro() const = 0;

};

#endif // FIGURA2D_H_INCLUDED
