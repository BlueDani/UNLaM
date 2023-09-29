#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED


#define ANIO_MIN        1900
#define ANIO_MAX        5000
#define ES_BISIESTO(x)  ( (x)%4 == 0 && (x)%100 != 0 ) || ( (x)%400 == 0 )

// ES_BISIESTO:
// Aquellos años que son divisibles entre 4, pero no entre 100, son bisiestos.
// Los años que son divisibles entre 100, pero no entre 400, no son bisiestos.
// Sin embargo, los años divisibles entre 100 y entre 400 sí que son bisiestos

typedef struct
{
    int dia,
        mes,
        anio;
}t_fecha;

int ingresar_fecha_DMA(t_fecha *fec);
void mostrar_fecha_DMA(const t_fecha *fec);
int validar_fecha(const t_fecha *fec);

#endif // FECHA_H_INCLUDED