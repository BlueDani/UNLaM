#include <stdio.h>
#include <stdlib.h>

#include "funciones.h"
#include "listaSimple.h"

int main()
{
    unsigned cantidadActualizaciones;

    printf("-> Contenido del archivo maestro <-\n");
    mostrarArchivoBinario_productos(NOMBRE_ARCHIVO_MAESTRO);

    cantidadActualizaciones = actualizarMaestro(NOMBRE_ARCHIVO_MAESTRO,
                              NOMBRE_ARCHIVO_NOVEDADES);

    printf("\n");
    printf("-> Contenido del archivo novedades <-\n");
    mostrarArchivoTextoLV_novedades(NOMBRE_ARCHIVO_NOVEDADES);

    printf("\n");
    printf("-> Contenido del archivo maestro actualizado <-\n");
    mostrarArchivoBinario_productos(NOMBRE_ARCHIVO_MAESTRO);

    printf("\n");
    printf("-> Se realizaron %u actualizaciones <-\n", cantidadActualizaciones);

    return 0;
}