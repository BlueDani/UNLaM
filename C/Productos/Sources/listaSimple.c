#include "listaSimple.h"

void crearLista( tLista * p )
{
    *p = NULL;
}

int insertarUltimoLista(tLista * p, const void * d, unsigned cantBytes)
{
    tNodo * nue;

    if( (nue=(tNodo*)malloc(sizeof(tNodo)))==NULL ||
            (nue->info=malloc(cantBytes))==NULL )
    {
        free(nue);
        return SIN_MEMORIA;
    }
    while(*p)
    {
        p = &(*p)->sig;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = NULL;
    *p = nue;

    return TODO_OK;
}

int buscarEnLista(tLista * p, const void *d, void *encontrado,
                  unsigned cantBytes,
                  int (*comparar)(const void *, const void *))
{
    while(*p)
    {
        if(comparar((*p)->info, d) == 0)
        {
            memcpy(encontrado, (*p)->info, MINIMO(cantBytes, (*p)->tamInfo));
            return ENCONTRADO;
        }
        p = &(*p)->sig;
    }
    return NO_ENCONTRADO;
}

void vaciarLista(tLista * p)
{
    tNodo *aux;

    while(*p)
    {
        aux = *p;
        *p = aux->sig;

        free(aux->info);
        free(aux);
    }
}