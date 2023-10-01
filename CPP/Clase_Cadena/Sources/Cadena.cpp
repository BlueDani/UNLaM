#include "Cadena.h"
#include <string.h>

#include <queue>

Cadena::Cadena()
{
    _cad = new char[1];
    *_cad = '\0';
    //_cad[0] = '\0';
}
Cadena::Cadena(const Cadena &objDer)
{
    _cad = new char[strlen(objDer._cad)+1];
    strcpy(_cad, objDer._cad);
}

Cadena::Cadena(const char *cad)
{
    _cad = new char[strlen(cad)+1];
    strcpy(_cad, cad);
}

Cadena::~Cadena()
{
    delete [] _cad;
}

Cadena& Cadena::operator=(const Cadena &objDer)
{
    if(this==&objDer)
    {
        return *this;
    }

    delete[]_cad;
    _cad = new char[strlen(objDer._cad)+1];
    strcpy(_cad, objDer._cad);

    return *this;

}

Cadena& Cadena::operator=(const char *cad)
{
    delete[]_cad;
    _cad = new char[strlen(cad)+1];
    strcpy(_cad, cad);

    return *this;
}

Cadena Cadena::operator+(const Cadena &objDer)const
{
    Cadena aux;
    delete [] aux._cad;

    aux._cad = new char[strlen(_cad)+strlen(objDer._cad)+1];
    strcpy(aux._cad, _cad);
    strcat(aux._cad, objDer._cad);

    return aux;
}

Cadena Cadena::operator+(const char *cad)const
{
    Cadena aux;
    delete [] aux._cad;

    aux._cad = new char[strlen(_cad)+strlen(cad)+1];
    strcpy(aux._cad, _cad);
    strcat(aux._cad, cad);

    return aux;
}

Cadena operator+(const char *cad, const Cadena &objDer)
{
    Cadena aux;
    delete [] aux._cad;

    aux._cad = new char[strlen(cad)+strlen(objDer._cad)+1];
    strcpy(aux._cad, cad);
    strcat(aux._cad, objDer._cad);

    return aux;
}

std::ostream& operator<<(std::ostream &salida, Cadena &objDer)
{
    salida << objDer._cad;
    return salida;
}

std::istream& operator>>(std::istream& entrada, Cadena& objDer)
{
    std::queue<char> colaChars;
    char c;
    int i = 0;

    while((c = entrada.get()) != '\n' && c != EOF)
        colaChars.push(c);

    if(strlen(objDer._cad) != colaChars.size())
    {
        delete [] objDer._cad;
        objDer._cad = new char[colaChars.size() + 1];
    }

    while(!colaChars.empty())
    {
        objDer._cad[i++] = colaChars.front();
        colaChars.pop();
    }

    objDer._cad[i] = '\0';

    return entrada;
}


unsigned Cadena::longitud()const
{
    return strlen(_cad);
}