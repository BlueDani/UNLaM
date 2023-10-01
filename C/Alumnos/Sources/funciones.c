#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funciones.h"

/******************************************************************************/
// ARCHIVO - INDICE ////////////////////////////////////////////////////////////

int crear_archivo_bin_alumnos(const char * path_alumnos)
{
    int cant_registros;

    // creo vector de alumnos como lote de prueba
    t_alumno alumnos[] =
    {
        {34667431, "Araujo Victoria", {21,7,1991}, 'F', {22,2,2017}, "ECO", 27, 'A', {}},
        {84900272, "Del Moral Oscar", {20,5,1994}, 'M', {15,1,2020}, "ELE", 20, 'A', {}},
        {76193899, "Justo Varela Aurelio", {13,10,1993}, 'M', {9,4,2020}, "ELE", 14, 'A', {}},
        {26771827, "Ochoa Zaira", {30,9,1996}, 'F', {18,9,2019}, "MED", 9, 'A', {}},
        {57070551, "Tapia Julian Francisco", {23,8,1991}, 'M', {29,4,2020}, "ADM", 1, 'A', {}},
    };

    // creo el archivo con el lote de prueba
    FILE *fp = fopen(path_alumnos, "wb");
    if(!fp)
    {
        printf("ERROR: crear archivo \"alumnos.dat\".\n");
        system("PAUSE");
        return ERROR_1;
    }

    fwrite(alumnos, sizeof(alumnos), 1, fp);
    fclose(fp);

    // seteo la cantidad de registros iniciales
    cant_registros = sizeof(alumnos)/sizeof(t_alumno);

    return cant_registros;
}

////////////////////////////////////////////////////////////////////////////////

t_indice * generar_indice_alumnos(const char *path, int cant_registros,
                                  int (*comparar)(const void *, const void *))
{
    FILE *fp;
    t_alumno alumno;
    t_indice *indice;
    t_indice *cpy_indice;

    unsigned int pos = 0;

    // abro archivo en modo lectura
    fp = fopen(path, "rb");
    if (!fp)
    {
        printf("ERROR: leer archivo \"alumnos.dat\".\n");
        system("PAUSE");
        return ERROR_2;
    }

    // reservo memoria para el vector indice segun la cantidad de alumnos del archivo
    indice = (t_indice *)malloc(sizeof(t_indice) * cant_registros);
    if (!indice)
    {
        printf("ERROR: reservar memoria.\n");
        system("PAUSE");
        return ERROR_2;
    }

    // creo auxiliar del vector indice para poder mover el puntero sin perder el inicio
    cpy_indice = indice;

    // recorro el archivo de alumnos cargando el indice
    fread(&alumno, sizeof(t_alumno), 1, fp);
    while(!feof(fp))
    {
        if(alumno.estado == 'A')
        {
            cpy_indice->dni = alumno.dni;
            cpy_indice->pos = pos;
            cpy_indice++;
        }
        pos++;
        fread(&alumno, sizeof(t_alumno), 1, fp);
    }

    // ordeno el indice por DNI
    ordenar_seleccion(indice, cant_registros, sizeof(t_indice), comparar);

    fclose(fp);

    return indice;
}

////////////////////////////////////////////////////////////////////////////////

int ordenar_seleccion(void *vec, size_t cantEle, size_t tamEle,
                      int (*comparar)(const void *, const void *))
{
    int i, j, pos_menor;

    for(i = 0; i < cantEle - 1; i++)
    {
        pos_menor = i;

        for(j = i + 1; j < cantEle; j++)
            if(comparar(vec + pos_menor*tamEle, vec + j*tamEle) > 0)
                pos_menor = j;

        if(!intercambiar(vec + i*tamEle,  vec + pos_menor*tamEle, tamEle))
            return ERROR_1;
    }
    return OK;
}

////////////////////////////////////////////////////////////////////////////////

int comparar_alumnos_indice(const void *a, const void *b)
{
    t_indice *aluA = (t_indice *)a;
    t_indice *aluB = (t_indice *)b;

    return aluA->dni - aluB->dni;
}

////////////////////////////////////////////////////////////////////////////////

int intercambiar(void *a, void *b, size_t tam)
{
    char *aux = malloc(tam);
    if (!aux)
    {
        printf("ERROR: reservar memoria.\n");
        system("PAUSE");
        return ERROR_1;
    }

    memcpy(aux, a, tam);
    memcpy(a, b, tam);
    memcpy(b, aux, tam);

    free(aux);
    return OK;
}


/******************************************************************************/
// OPCIONES DEL MENU //////////////////////////////////////////////////////////

void mostrar_alumno(const void *alu)
{
    t_alumno *alumno;

    // creo titulo para mostrar los alumnos
    if(!alu)
    {
        printf("DNI      NOMBRE Y APELLIDO                                  FEC. NAC.  SEXO FEC. ING.  CARRERA CANT. MATERIAS ESTADO FEC. BAJA  \n");
        printf("-------- -------------------------------------------------- ---------- ---- ---------- ------- -------------- ------ ---------- \n");
        return;
    }

    // muestro alumno completo
    alumno = (t_alumno *)alu;

    printf("%8ld %-*.*s  %02d/%02d/%04d %4c %02d/%02d/%04d     %s %14d %6c %02d/%02d/%04d\n",
           alumno->dni,
           (int)sizeof(alumno->apyn)-1,
           (int)sizeof(alumno->apyn)-1,
           alumno->apyn,
           alumno->fec_nac.dia,
           alumno->fec_nac.mes,
           alumno->fec_nac.anio,
           alumno->sexo,
           alumno->fec_ing.dia,
           alumno->fec_ing.mes,
           alumno->fec_ing.anio,
           alumno->carrera,
           alumno->cant_materias_aprob,
           alumno->estado,
           alumno->fec_baja.dia,
           alumno->fec_baja.mes,
           alumno->fec_baja.anio
          );
}

/// ALTA ///////////////////////////////////////////////////////////////////////

t_indice * dar_alta_alumno(t_indice *indice, int *cant_registros,
                           t_alumno *alumno, const char *path,
                           int (*comparar)(const void *, const void *))
{
    long int pos;
    t_indice *cpy_indice;

    // abro archivo en modo "append" porque siempre agregaremos las altas nuevas al final
    FILE *fp = fopen(path, "ab");
    if(!fp)
    {
        printf("ERROR: leer archivo \"alumnos.dat\".\n");
        return ERROR_2;
    }
    // guardo el nuevo alumno en el archivo
    fwrite(alumno, sizeof(t_alumno), 1, fp);
    // calculo la posicion que el nuevo alumno tiene en el archivo
    pos = ftell(fp)/sizeof(t_alumno)-1;
    // sumo el alta en la cantidad de registros
    (*cant_registros)++;

    // actualizo el indice con el alumno recien dado de alta:
    // 1 - reservo memoria para un alumno mas
    indice = (t_indice *)realloc(indice, (sizeof(t_indice) * (*cant_registros)));
    if(!indice)
    {
        printf("ERROR: reservar memoria.\n");
        return ERROR_2;
    }
    // 2 - guardo clave del alumno y su posicion en el indice
    cpy_indice = indice;
    cpy_indice+=(*cant_registros)-1;
    cpy_indice->dni = alumno->dni;
    cpy_indice->pos = pos;

    // ordeno el indice de nuevo, considerando el nuevo alumno
    ordenar_seleccion(indice, *cant_registros, sizeof(t_indice), comparar);

    fclose(fp);

    return indice;
}

////////////////////////////////////////////////////////////////////////////////

int ingresar_validar_dni(t_alumno *alu)
{
    // dni
    printf("\nIngresar DNI (10000000 a 99999999): ");
    scanf("%ld", &alu->dni);

    if(!ES_DNI_VALIDO(alu->dni))
    {
        return ERROR_1;
    }
    return OK;
}

////////////////////////////////////////////////////////////////////////////////

int ingresar_alumno(t_alumno *alu)
{
    char *carrera;

    printf("\nIngresar datos Alumno:\n");

    // apyn
    printf("\tApellido y Nombre: ");
    fflush(stdin);
    scanf("%49[^\n]s", alu->apyn);

    // sexo
    printf("\tSexo (F/M): ");
    fflush(stdin);
    scanf("%c", &alu->sexo);
    alu->sexo = toupper(alu->sexo);

    // fec nac
    printf("\tFecha de Nacimiento (dd/mm/aaaa): ");
    ingresar_fecha_DMA(&alu->fec_nac);

    // fec ing
    printf("\tFecha de Ingreso (dd/mm/aaaa): ");
    ingresar_fecha_DMA(&alu->fec_ing);

    // carrera
    printf("\tCarrera: ");
    fflush(stdin);
    scanf("%3s", alu->carrera);
    carrera = alu->carrera;
    while(*carrera)
    {
        *carrera=toupper(*carrera);
        carrera++;
    }

    // cant materias aprobadas
    printf("\tCantidad de Materias Aprobadas: ");
    fflush(stdin);
    scanf("%d", &alu->cant_materias_aprob);

    // estado
    alu->estado = 'A';

    // fec baja
    alu->fec_baja.dia = 0;
    alu->fec_baja.mes = 0;
    alu->fec_baja.anio = 0;

    return OK;
}

////////////////////////////////////////////////////////////////////////////////

int validar_alumno(const t_alumno *alu)
{
    // apyn
    if(strlen(alu->apyn)==0)
    {
        printf("ERROR: el Nombre del alumno no puede estar vacio.\n");
        return ERROR_1;
    }

    // sexo
    if(!ES_SEXO_VALIDO(alu->sexo))
    {
        printf("ERROR: el Sexo ingresado no es valido.\n");
        return ERROR_1;
    }

    // fec nac
    if(!validar_fecha(&alu->fec_nac))
    {
        printf("ERROR: la Fecha de Nacimiento ingresada no es valida.\n");
        return ERROR_1;
    }

    // fec ing
    if(!validar_fecha(&alu->fec_ing))
    {
        printf("ERROR: la Fecha de Ingreso ingresada no es valida.\n");
        return ERROR_1;
    }

    // carrera
    if(!validar_carrera(alu->carrera))
    {
        printf("ERROR: la Carrera ingresada no es valida. Opciones validas: "
               "[INF, ELE, IND, ECO, DER, ADM, MED, EDF, FIL]\n");
        return ERROR_1;
    }

    // cant materias aprobadas
    if(!ES_CANT_VALIDA(alu->cant_materias_aprob) || isalpha(alu->cant_materias_aprob))
    {
        printf("ERROR: la Cantidad de Materias ingresada no es valida.\n");
        return ERROR_1;
    }

    return OK;
}

////////////////////////////////////////////////////////////////////////////////

int validar_carrera(const char *carrera)
{
    int i;

    const char carreras [][TAM_CARRERA] =
    {
        "INF",
        "ELE",
        "IND",
        "ECO",
        "DER",
        "ADM",
        "MED",
        "EDF",
        "FIL"
    };

    unsigned cant_carreras = sizeof(carreras)/sizeof(TAM_CARRERA);

    for ( i=0 ; i<cant_carreras ; i++)
    {
        if(strcmp(carrera, carreras[i])==0)
            return ENCONTRADO;
    }
    return NO_ENCONTRADO;
}


/// BAJA ///////////////////////////////////////////////////////////////////////

t_indice * dar_baja_alumno(t_indice *indice, int *cant_registros,
                           t_indice *alu_baja, const char *path,
                           t_fecha fec_baja)
{
    t_alumno alumno;
    t_indice *ult_regitro = indice + *cant_registros -1;

    // abro archivo para actualizarlo
    FILE *fp = fopen(path, "r+b");
    if(!fp)
    {
        printf("ERROR: leer archivo \"alumnos.dat\".\n");
        system("PAUSE");
        return ERROR_2;
    }

    // voy a buscar el alumno en el archivo usando su posicion guardada en el indice
    fseek(fp, alu_baja->pos * sizeof(t_alumno), SEEK_SET);
    fread(&alumno, sizeof(t_alumno), 1, fp);

    // actualizo los campos de alumno
    alumno.estado = 'B';
    alumno.fec_baja.dia = fec_baja.dia;
    alumno.fec_baja.mes = fec_baja.mes;
    alumno.fec_baja.anio = fec_baja.anio;

    // actualizo el alumno en el archivo (no se borra el registro, sino que queda como BAJA)
    fseek(fp, -1L * (long)sizeof(t_alumno), SEEK_CUR);
    fwrite(&alumno, sizeof(t_alumno), 1, fp);

    // actualizo  indice (de aca si se borra el alumno, se lo pisa trasladando todos los alumnos que le siguen desde su posicion en el vector)
    while(alu_baja < ult_regitro)
    {
        *alu_baja = *(alu_baja+1);
        alu_baja++;
    }

    // actualizo cantidad de registros en Alta para ajustar la reserva de memoria
    (*cant_registros)--;
    indice = (t_indice *)realloc(indice, (sizeof(t_indice) * (*cant_registros)));
    if(!indice)
    {
        printf("ERROR: reservar memoria.\n");
        fclose(fp);
        return ERROR_2;
    }

    fclose(fp);
    return indice;
}

/// BUSCAR /////////////////////////////////////////////////////////////////////

t_indice * buscar_alumno_dni(t_indice *indice, const char *path,
                             int cant_registros, t_indice *alumno_a_buscar,
                             void (*mostrar)(const void *))
{
    t_alumno alumno;
    t_indice *encontrado;

    // abro archivo en modo lectura
    FILE *fp = fopen(path, "rb");
    if(!fp)
    {
        printf("ERROR: leer archivo \"alumnos.dat\".\n");
        return ERROR_2;
    }

    // llamo a una busqueda binaria sobre el indice para determinar si el alumno existe entre los dados de Alta
    encontrado = busqueda_binaria(indice, alumno_a_buscar, sizeof(t_indice), cant_registros, comparar_alumnos_indice);
    if(encontrado)
    {
        // mostrar el alumno es opcional
        if(mostrar)
        {
            // busco y traigo el alumno en el archivo, usando su posicion que guarde en el indice
            fseek(fp, (long)encontrado->pos * (long)sizeof(t_alumno), SEEK_SET);
            fread(&alumno, sizeof(t_alumno), 1, fp);
            mostrar(NULL);      // para mostrar el titulo
            mostrar(&alumno);   // para mostrar los campos de alumno debajo del titulo
        }
        fclose(fp);
        return encontrado;
    }

    fclose(fp);
    return ERROR_2;
}

void * busqueda_binaria(void* vec, const void* dato_a_buscar, unsigned tam_dato,
                        unsigned cant_ele, int(*comparar)(const void*, const void*))
{
    int pri = 0;
    int ult = cant_ele-1;
    int medio;
    void *elemento_medio;
    int res_cmp;

    while(pri <= ult)
    {
        medio = (pri + ult)/2;
        elemento_medio = vec + medio*tam_dato;
        res_cmp = comparar(dato_a_buscar, elemento_medio);

        if(res_cmp == 0)
        {
            // ENCONTRADO
            return elemento_medio;
        }
        else if(res_cmp < 0)
        {
            // El dato a buscar es menor, buscar en la mitad inferior
            ult = medio - 1;
        }
        else
        {
            // El dato a buscar es mayor, buscar en la mitad superior
            pri = medio + 1;
        }
    }
    // No se encontró el elemento
    return NULL;
}


/// LISTAR BAJAS ///////////////////////////////////////////////////////////////

int mostrar_archivo_bin_bajas(const char *path)
{
    t_alumno alumno;

    // abro archivo en modo lectura
    FILE *fp = fopen(path, "rb");
    if(!fp)
    {
        printf("ERROR: leer archivo \"alumnos.dat\".\n");
        return ERROR_1;
    }

    // muestro el titulo con los campos de alumno
    mostrar_alumno(NULL);

    fread(&alumno, sizeof(t_alumno), 1, fp);
    while(!feof(fp))
    {
        // las bajas no se deben mostrar
        if(alumno.estado == 'B')
        {
            mostrar_alumno(&alumno);
        }
        fread(&alumno, sizeof(t_alumno), 1, fp);
    }
    fclose(fp);
    return OK;
}

/// LISTAR ORDENADO ////////////////////////////////////////////////////////////

int mostrar_archivo_bin_ordenado(t_indice *indice, int cant_registros,
                                 const char *path,
                                 void (*mostrar)(const void *))
{
    t_alumno alumno;

    // abro archivo en modo lectura
    FILE *fp = fopen(path, "rb");
    if (!fp)
    {
        printf("ERROR: leer archivo \"alumnos.dat\".\n");
        return ERROR_1;
    }

    // muestro el titulo con los campos de alumno
    mostrar(NULL);

    // recorro archivo e indice:
    // leo la posicion de cada alumno en el indice y lo voy a buscar al archivo para mostrarlo ordenado pero con todos sus campos
    while(cant_registros)
    {
        fseek(fp, indice->pos * sizeof(t_alumno), SEEK_SET);
        fread(&alumno, sizeof(t_alumno), 1, fp);
        mostrar(&alumno);

        indice++;
        cant_registros--;
    }

    fclose(fp);
    return OK;
}

/******************************************************************************/
// OTRAS ///////////////////////////////////////////////////////////////////////

//void mostrar_indice(t_indice *indice, int cant_reg)
//{
//    printf("Indice:\n");
//    while(cant_reg)
//    {
//        printf("dni: %ld, pos: %d\n", indice->dni, indice->pos);
//        cant_reg--;
//        indice++;
//    }
//}
//
//int mostrar_archivo_bin_completo(const char *path, void *dato, size_t tamDato,
//                        void (*mostrar)(const void *))
//{
//    FILE *fp = fopen(path, "rb");
//    if(!fp)
//    {
//        printf("Error: leer archivo.\n");
//        return ERROR;
//    }
//
//    mostrar(NULL);
//
//    fread(dato, tamDato, 1, fp);
//    while(!feof(fp))
//    {
//        mostrar(dato);
//        fread(dato, tamDato, 1, fp);
//    }
//    fclose(fp);
//    return OK;
//}
//
//int mostrar_archivo_bin_ordenado(t_indice *indice, int cant_registros,
//                                 const char *path)
//{
//    t_alumno alumno;
//
//    FILE *fp = fopen(path, "rb");
//    if (!fp)
//    {
//        printf("Error: leer archivo\n");
//        return ERROR;
//    }
//
//    mostrar_alumno(NULL);
//
//    while(cant_registros)
//    {
//        fseek(fp, indice->pos * sizeof(t_alumno), SEEK_SET);
//        fread(&alumno, sizeof(t_alumno), 1, fp);
//        mostrar_alumno(&alumno);
//
//        indice++;
//        cant_registros--;
//    }
//
//    return OK;
//}