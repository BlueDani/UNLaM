#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#define TAM_OPCIONES    61

char menu(const char m[][TAM_OPCIONES], const char *titulo);
char leer_opcion(const char m[][TAM_OPCIONES], const char *titulo, const char *msj);

#endif // MENU_H_INCLUDED