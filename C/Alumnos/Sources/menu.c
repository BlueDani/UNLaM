#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "menu.h"


char menu(const char m[][TAM_OPCIONES], const char *titulo)
{
    char op;
    op = leer_opcion(m, titulo, "Ingresar opcion: ");

    // evaluo la opcion ingresada (primera vez), si el strchr devuelve NULL es porque no está en "ABCDEF"
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

    // CLEAR SCREEN: will clear the previous output and print the next statement on the console
    // usarlo con system("PAUSE") en cada opcion del switch, sino apenas lo muestra borra lo que muestra la consola pantalla
    system("CLS");


    printf("\n\n %s \n", titulo);

    for ( i=1 ; i <= strlen(m[0]) ; i++)
         // muestro el menu en formato LETRA - DESCRIPCION
        printf("\n %c - %s", m[0][i-1], m[i]);

    // muestro el mensaje pasado por parametro
    printf("\n\n%s ", msj);

    // leo la opcion del usuario
    fflush(stdin);
    scanf("%c", &opcion);

    return toupper(opcion);
}