#ifndef CADENA_H_INCLUDED
#define CADENA_H_INCLUDED

#include <iostream>


class Cadena
{
    private:
        char * _cad;

    public:
        Cadena();               // constructor por default
        Cadena(const Cadena &); // constructor por copia
        Cadena(const char *);   // constructor parametrizado
        ~Cadena();

        Cadena& operator=(const Cadena &);
        Cadena& operator=(const char *);
        Cadena operator+(const Cadena&)const;
        Cadena operator+(const char *cad)const;
        friend Cadena operator+(const char *, const Cadena &);
        friend std::ostream& operator<<(std::ostream &, Cadena &);
        friend std::istream& operator>>(std::istream &, Cadena &);

        unsigned longitud()const;
};

#endif // CADENA_H_INCLUDED