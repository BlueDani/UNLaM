#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "menu.h"


char menu(const char m[][TAM_OPCIONES], const char *titulo)
{
    char op;
    op = leer_opcion(m, titulo, "Ingresar opcion: ");

    while(!strchr(m[0], op))
        op = leer_opcion(m, titulo,
                        "La opcion ingresada no es valida. "
                        "Ingresar opcion nuevamente: ");

    return op;
}


char leer_opcion(const char m[][TAM_OPCIONES], const char *titulo, const char *msj)
{
    char opcion;
    int i;

    system("CLS");

    printf("\n\n %s \n", titulo);

    for ( i=1 ; i <= strlen(m[0]) ; i++)
        printf("\n %c - %s", m[0][i-1], m[i]);

    printf("\n\n%s ", msj);

    fflush(stdin);
    scanf("%c", &opcion);

    return toupper(opcion);
}