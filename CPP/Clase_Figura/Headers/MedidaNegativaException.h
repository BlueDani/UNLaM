#ifndef MEDIDANEGATIVAEXCEPTION_H_INCLUDED
#define MEDIDANEGATIVAEXCEPTION_H_INCLUDED

#include <iostream>
#include <exception>

using namespace std;

class MedidaNegativaException : public exception
{
private:
    int motivo;

public:
    MedidaNegativaException(int motivo) throw()
        : exception(), motivo(motivo) {}

    virtual const char * what() throw()
    {
        switch(motivo)
        {
            case 1: return "Circulo";
            case 2: return "Cuadrado";
            case 3: return "Triangulo";
        }
        return "Error inesperado";
    }
};

#endif // MEDIDANEGATIVAEXCEPTION_H_INCLUDED
