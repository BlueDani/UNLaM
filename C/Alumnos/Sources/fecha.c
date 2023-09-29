#include <stdio.h>

#include "fecha.h"


int ingresar_fecha_DMA(t_fecha *fec)
{
    fec->dia = 0;
    fec->mes = 0;
    fec->anio = 0;

    fflush(stdin);
    scanf("%d/%d/%d", &fec->dia, &fec->mes, &fec->anio);

    return fec->dia && fec->mes && fec->anio;
}

void mostrar_fecha_DMA(const t_fecha *fec)
{
    printf("%02d/%02d/%04d", fec->dia, fec->mes, fec->anio); ///
}


int validar_fecha(const t_fecha *fec)
{
    const char dias[][12] =
    {
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };
    return  fec->anio>=ANIO_MIN && fec->anio<=ANIO_MAX &&
            fec->mes>0 && fec->mes<=12 &&
            fec->dia>0 && fec->dia<=dias[ES_BISIESTO(fec->anio)][fec->mes - 1];
}