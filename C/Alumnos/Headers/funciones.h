#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stddef.h>
#include "tipos.h"

#define PATH_ALUMNOS    "alumnos.dat"

#define OK              1
#define ERROR_1         0
#define ERROR_2         NULL

#define ENCONTRADO      1
#define NO_ENCONTRADO   0



/******************************************************************************/
// ARCHIVO - INDICE ////////////////////////////////////////////////////////////

int crear_archivo_bin_alumnos(const char * path_alumnos);
t_indice * generar_indice_alumnos(const char *path, int cant_registros,
                                  int (*comparar)(const void *, const void *));

int ordenar_seleccion(void *vec, size_t cantEle, size_t tamEle,
                      int (*comparar)(const void *, const void *));
int comparar_alumnos_indice(const void *a, const void *b);
int intercambiar(void *a, void *b, size_t tam);


/******************************************************************************/
// OPCIONES ////////////////////////////////////////////////////////////////////

void mostrar_alumno(const void *alu);

t_indice * dar_alta_alumno(t_indice *indice, int *cant_registros,
                           t_alumno *alumno, const char *path,
                           int (*comparar)(const void *, const void *));
int ingresar_validar_dni(t_alumno *alu);
int ingresar_alumno(t_alumno *alu);
int validar_alumno(const t_alumno *alu);
int validar_carrera(const char *carrera);

t_indice * dar_baja_alumno(t_indice *indice, int *cant_registros,
                           t_indice *alu_baja, const char *path,
                           t_fecha fec_baja);

t_indice * buscar_alumno_dni(t_indice *indice, const char *path,
                             int cant_registros, t_indice *alumno_a_buscar,
                             void (*mostrar)(const void *));
void * busqueda_binaria(void* vec, const void* dato_a_buscar, unsigned tam_dato,
                        unsigned cant_ele, int(*comparar)(const void*, const void*));

int mostrar_archivo_bin_bajas(const char *path);

int mostrar_archivo_bin_ordenado(t_indice *indice, int cant_registros,
                                 const char *path,
                                 void (*mostrar)(const void *));


/******************************************************************************/
// OTRAS ///////////////////////////////////////////////////////////////////////
//int mostrar_archivo_bin_completo(const char *path, void *dato, size_t tamDato,
//                        void (*mostrar)(const void *));
//int mostrar_archivo_bin_ordenado(t_indice *indice, int cant_registros, const char *path);
//void mostrar_indice(t_indice *indice, int cant_reg);

#endif // FUNCIONES_H_INCLUDED