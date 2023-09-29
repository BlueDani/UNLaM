#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>

#include "listaSimple.h"

#define NOMBRE_ARCHIVO_MAESTRO "maestroProductos.dat"
#define NOMBRE_ARCHIVO_NOVEDADES "novedades.txt"

#define TAM_LINEA 100

#define ERROR_ABRIRARCHIVO -2
#define ERROR_INSERCIONLISTA -1
#define TODO_OK 1

typedef struct
{
    int dia,
        mes,
        anio;
} tFecha;

typedef struct
{
    long idProducto;
    char descripcion[26];
    tFecha fecUltAct;
    int cantidad;
    float precioUnitario;
} tProducto;

typedef struct
{
    long idProducto;
    char tipoOperacion;
    int cantidad;
} tNovedad;

typedef struct
{
    long idProducto;
    unsigned pos;
} tIndice;

int actualizarMaestro(const char *, const char * );
void parsearNovedad_LV(char *, tNovedad * );
int compararIdS(const void *, const void * );
int mostrarArchivoBinario_productos(const char * );
void mostrarProducto(const tProducto * );
int mostrarArchivoTextoLV_novedades(const char * );
void mostrarNovedad(const tNovedad * );


#endif // FUNCIONES_H_INCLUDED