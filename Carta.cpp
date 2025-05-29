#include "Carta.h"
#include <iostream>
using namespace std;

// Constructor
Carta::Carta(string _color) {
    color = _color;
}

// Método para obtener el color de la carta
string Carta::getColor() {
    return color;
}

// Método para mostrar la carta
void Carta::mostrar() {
    cout << "Carta de color " << color;
}
