#include "funciones.h"


int actualizarMaestro(const char * nombreArchivoMaestro,
                      const char * nombreArchivoNovedades)
{
    FILE * fpMaestro;
    FILE * fpNovedades;
    tProducto producto;
    tNovedad novedad;
    tIndice indice;
    tLista listaIndice;
    char linea[TAM_LINEA];
    unsigned cantActualizaciones = 0;
    indice.pos = 0;


    fpMaestro = fopen(nombreArchivoMaestro, "rb");
    if(!fpMaestro)
    {
        return ERROR_ABRIRARCHIVO;
    }
    fpNovedades = fopen(nombreArchivoNovedades, "rt");
    if(!fpNovedades)
    {
        fclose(fpMaestro);
        return ERROR_ABRIRARCHIVO;
    }

    crearLista);

    /// Se carga Maestro en lista indice:
    fread(&producto, sizeof(tProducto), 1, fpMaestro);
    while(!feof(fpMaestro))
    {
        indice.idProducto = producto.idProducto;
        if(!insertarUltimoLista(&listaIndice, &indice, sizeof(tIndice)))
        {
            return ERROR_INSERCIONLISTA;
        }
        indice.pos++;
        fread(&producto, sizeof(tProducto), 1, fpMaestro);
    }
    fclose(fpMaestro);


    /// Se actualiza maestro:
    fpMaestro = fopen(nombreArchivoMaestro, "r+b");
    if(!fpMaestro)
    {
        return ERROR_ABRIRARCHIVO;
    }

    while(fgets(linea, TAM_LINEA, fpNovedades))
    {
        parsearNovedad_LV(linea, &novedad);

        if(buscarEnLista(&listaIndice, &novedad, &indice, sizeof(tIndice),
                         compararIdS) == ENCONTRADO)
        {
            fseek(fpMaestro,
                  (long)indice.pos*(long)(sizeof(tProducto)),
                  SEEK_SET);
            fread(&producto, sizeof(tProducto), 1, fpMaestro);
            switch(novedad.tipoOperacion)
            {
            case 'I':
                producto.cantidad += novedad.cantidad;
                break;
            case 'E':
                producto.cantidad -= novedad.cantidad;
            }
            fseek(fpMaestro, -1L * (long)sizeof(tProducto), SEEK_CUR);
            fwrite(&producto, sizeof(tProducto), 1, fpMaestro);
            cantActualizaciones++;
        }
    }

    vaciarLista(&listaIndice);
    fclose(fpMaestro);
    fclose(fpNovedades);
    return cantActualizaciones;
}


void parsearNovedad_LV(char * linea, tNovedad * nov)
{
    char * auxLinea;
    auxLinea = strchr(linea,'\n');
    *auxLinea = '\0';

    auxLinea = strrchr(linea, '|');
    sscanf(auxLinea+1, "%d", &nov->cantidad);
    *auxLinea = '\0';

    auxLinea = strrchr(linea, '|');
    sscanf(auxLinea+1, "%c", &nov->tipoOperacion);
    *auxLinea = '\0';

    sscanf(linea, "%ld", &nov->idProducto);
}

int compararIdS(const void * id1, const void * id2)
{
    tIndice * auxId1 = (tIndice *)id1;
    tNovedad * auxId2 = (tNovedad *)id2;

    return auxId1->idProducto - auxId2->idProducto;
}

int mostrarArchivoBinario_productos(const char * nombreArchivo)
{
    tProducto producto;
    FILE * fp;

    fp = fopen(nombreArchivo, "rb");
    if(!fp)
    {
        return ERROR_ABRIRARCHIVO;
    }

    fread(&producto, sizeof(tProducto), 1, fp);
    while(!feof(fp))
    {
        mostrarProducto(&producto);
        fread(&producto, sizeof(tProducto), 1, fp);
    }
    fclose(fp);
    return TODO_OK;
}

void mostrarProducto(const tProducto * prod)
{
    printf("%ld %s %d/%d/%d %d %.2f\n",
           prod->idProducto,
           prod->descripcion,
           prod->fecUltAct.dia,
           prod->fecUltAct.mes,
           prod->fecUltAct.anio,
           prod->cantidad,
           prod->precioUnitario);
}

int mostrarArchivoTextoLV_novedades(const char * nombreArchivo)
{
    char linea[TAM_LINEA];
    tNovedad nov;

    FILE * fp = fopen(nombreArchivo, "rt");
    if(!fp)
    {
        return ERROR_ABRIRARCHIVO;
    }
    while(fgets(linea, TAM_LINEA, fp))
    {
        parsearNovedad_LV(linea, &nov);
        mostrarNovedad(&nov);
    }
    fclose(fp);
    return TODO_OK;
}


void mostrarNovedad(const tNovedad * nov)
{
    printf("%ld %c %d\n", nov->idProducto, nov->tipoOperacion, nov->cantidad);
}