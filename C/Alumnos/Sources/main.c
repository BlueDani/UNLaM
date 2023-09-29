#include <stdio.h>
#include <stdlib.h>

#include "fecha.h"
#include "menu.h"
#include "tipos.h"
#include "funciones.h"

#define ERROR_CREAR_ARCHIVO -1

int main()
{

    t_fecha fecha_proceso;
    int cant_registros;
    t_alumno alumno;
    t_indice aux_alumno;
    t_indice *indice;
    t_indice *encontrado;

    char op;
    const char opciones [][TAM_OPCIONES] =
    {
        "ABCDEF",
        "Dar de alta a un alumno.",
        "Dar de baja a un alumno.",
        "Buscar y ver un alumno por DNI.",
        "Listar los alumnos dados de baja.",
        "Listar todos los alumnos en alta (ordenados por DNI).",
        "Salir."
    };

    // FECHA ///////////////////////////////////////////////////////////////////
    printf("Ingresar fecha de hoy (dd/mm/aaaa): ");
    ingresar_fecha_DMA(&fecha_proceso);

    while(!validar_fecha(&fecha_proceso))
    {
        printf("La fecha ingresada no es valida.\n\n"
               "Ingresar nuevamente fecha (dd/mm/aaa): ");
        ingresar_fecha_DMA(&fecha_proceso);
    }

    printf("\nFecha ingresada: ");
    mostrar_fecha_DMA(&fecha_proceso);
    printf("\n");
    system("PAUSE");


    // ARCHIVO - INDICE ////////////////////////////////////////////////////////

    if(!(cant_registros = (crear_archivo_bin_alumnos(PATH_ALUMNOS))))
    {
        exit(ERROR_CREAR_ARCHIVO);
    }
    indice = generar_indice_alumnos(PATH_ALUMNOS, cant_registros, comparar_alumnos_indice);


    // MENU ////////////////////////////////////////////////////////////////////
    do
    {
        op = menu(opciones, "Menu Principal");

        switch (op)
        {
        case 'A':
            printf("A - Dar de alta a un alumno:\n");
            if(ingresar_validar_dni(&alumno))
            {
                aux_alumno.dni = alumno.dni;
                encontrado = buscar_alumno_dni(indice, PATH_ALUMNOS, cant_registros, &aux_alumno, NULL);
                if(!encontrado)
                {
                    ingresar_alumno(&alumno);
                    if(validar_alumno(&alumno))
                    {
                        indice = dar_alta_alumno(indice, &cant_registros, &alumno, PATH_ALUMNOS, comparar_alumnos_indice);
                        if(indice)
                        {
                            printf("El alumno %ld fue dado de alta.\n", alumno.dni);
                        }
                    }
                    else
                    {
                        printf("El Alumno no fue ingresado.\n");
                    }
                }
                else
                {
                    printf("ERROR: Alta Alumno. El alumno ya se encuentra dado de Alta.\n\n");
                }
            }
            else
            {
                printf("ERROR: el DNI ingresado no es valido.\n");
            }
            system("PAUSE");
            break;

        case 'B':
            printf("B - Dar de baja a un alumno:\n");
            if(ingresar_validar_dni(&alumno))
            {
                aux_alumno.dni = alumno.dni;
                encontrado = buscar_alumno_dni(indice, PATH_ALUMNOS, cant_registros, &aux_alumno, NULL);
                if(encontrado)
                {
                    indice = dar_baja_alumno(indice, &cant_registros, encontrado, PATH_ALUMNOS, fecha_proceso);
                    if(indice)
                    {
                        printf("El alumno %ld fue dado de baja.\n", alumno.dni);
                    }
                }
                else
                {
                    printf("ERROR: Baja Alumno. El alumno no existe.\n");
                }
            }
            else
            {
                printf("ERROR: el DNI ingresado no es valido.\n");
            }
            system("PAUSE");
            break;

        case 'C':
            printf("Buscar y ver un alumno por DNI:\n");
            if(ingresar_validar_dni(&alumno))
            {
                aux_alumno.dni = alumno.dni;
                encontrado = buscar_alumno_dni(indice, PATH_ALUMNOS, cant_registros, &aux_alumno, mostrar_alumno);
                if(!encontrado)
                {
                    printf("ERROR: Buscar Alumno. Alumno no encontrado.\n");
                }
            }
            system("PAUSE");
            break;

        case 'D':
            printf("D - Listar Bajas:\n");
            mostrar_archivo_bin_bajas(PATH_ALUMNOS);
            system("PAUSE");
            break;

        case 'E':
            printf("E - Listar alumnos en alta ordenados por DNI:\n");
            mostrar_archivo_bin_ordenado(indice, cant_registros, PATH_ALUMNOS, mostrar_alumno);
            system("PAUSE");
            break;
        }
    }
    while(op!='F');

    free(indice);

    return 0;
}