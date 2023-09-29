#ifndef LISTASIMPLE_H_INCLUDED
#define LISTASIMPLE_H_INCLUDED

#include <string.h>
#include <stdlib.h>

#define MINIMO(x,y) (x)<(y) ? (x) : (y)

#define TODO_OK 1
#define SIN_MEMORIA 0

#define ENCONTRADO 1
#define NO_ENCONTRADO 0

typedef struct sNodo
{
    void * info;
    unsigned tamInfo;
    struct sNodo * sig;

} tNodo;

typedef tNodo * tLista;

void crearLista( tLista * p );
int insertarUltimoLista(tLista * p, const void * d, unsigned cantBytes);
int buscarEnLista(tLista * p,
                  const void *d,
                  void *encontrado,
                  unsigned cantBytes,
                  int (*comparar)(const void *, const void *));
void vaciarLista(tLista * p);


#endif // LISTASIMPLE_H_INCLUDED