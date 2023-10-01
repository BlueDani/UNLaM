#include <iostream>

#include "Figura2D.h"
#include "Circulo.h"
#include "Cuadrado.h"
#include "Triangulo.h"

using namespace std;

int main()
{
    Figura2D * figuraBidimensional;

    float radio = 5.0F;
    float lado = 2.0F;
    float lado1 = 3.0F;
    float lado2 = 4.0F;
    float lado3 = 2.0F;

    try
    {
        figuraBidimensional = new Circulo(radio);
        float area1 = figuraBidimensional -> area();
        float perimetro1 = figuraBidimensional -> perimetro();
        cout << "Circulo area: " << area1 << endl;
        cout << "Circulo perimetro: " << perimetro1 << endl;
        delete figuraBidimensional;

        figuraBidimensional = new Cuadrado(lado);
        cout << "Cuadrado area: " << figuraBidimensional -> area() << endl;
        cout << "Cuadrado perimetro: " << figuraBidimensional -> perimetro()<< endl;
        delete figuraBidimensional;

        try
        {
            figuraBidimensional = new Triangulo(lado1, lado2, lado3);
            cout << "Triangulo area: " << figuraBidimensional -> area() << endl;
            cout << "Triangulo perimetro: " << figuraBidimensional -> perimetro() << endl;
            delete figuraBidimensional;
        }
        catch(ConstruccionTrianguloException &cte)
        {
            cout << "Excepcion: " << cte.what() << endl;
        }
    }
    catch(MedidaNegativaException &mne)
    {
        cout << "Excepcion: Error de Medida negativa en el: " << mne.what() << endl;
    }

    return 0;
}
