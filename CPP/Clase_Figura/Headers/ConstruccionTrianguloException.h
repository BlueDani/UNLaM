#ifndef CONSTRUCCIONTRIANGULOEXCEPTION_H_INCLUDED
#define CONSTRUCCIONTRIANGULOEXCEPTION_H_INCLUDED

#include <exception>

using namespace std;

class ConstruccionTrianguloException : public exception
{
public:
    ConstruccionTrianguloException() : exception() {}
    const char *what() throw()
    {
        return "Error de construccion de triangulo.";
    }
};

#endif // CONSTRUCCIONTRIANGULOEXCEPTION_H_INCLUDED
