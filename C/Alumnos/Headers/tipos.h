#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

#include "fecha.h"

#define TAM_APYN                50
#define TAM_CARRERA             4
#define ES_DNI_VALIDO(x)        ( (x)>=10000000 && (x)<=99999999 )
#define ES_SEXO_VALIDO(x)       ( (x)=='F' || (x)=='M' )
#define ES_CANT_VALIDA(x)       ( (x)>=0 )

typedef struct
{
    long        dni;
    char        apyn[TAM_APYN];
    t_fecha     fec_nac;
    char        sexo;
    t_fecha     fec_ing;
    char        carrera[TAM_CARRERA];
    int         cant_materias_aprob;
    char        estado;
    t_fecha     fec_baja;
}t_alumno;


typedef struct
{
    long dni;
    int pos;
}t_indice;


#endif // TIPOS_H_INCLUDED