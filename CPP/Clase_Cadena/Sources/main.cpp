#include <iostream>

#include "Cadena.h"

using namespace std;

int main()
{
    Cadena c1("una cadena"),
           c2(c1),
           c3(c1 + c2),
           c4, c5, c6;

    c2 = "otro ejemplo de cadena";
    c4 = "otra cadena de varios caracteres";
    cout << "Longitud de c1 = " << c1.longitud() << endl;
    cout << "Longitud de c2 = " << c2.longitud() << endl;
    cout << "Longitud de c3 = " << c3.longitud() << endl;
    cout << "Longitud de c4 = " << c4.longitud() << endl;

    cout << "Ingresar cadena: ";
    c4 = c1 + " de varios caracteres";
    cin >> c5;
    c6 = "Esta es " + c1;
    cout << "c1 = " << c1 << endl
         << "c2 = " << c2 << endl
         << "c3 = " << c3 << endl
         << "c4 = " << c4 << endl
         << "c5 = " << c5 << endl
         << "c6 = " << c6 << endl;

    return 0;
}