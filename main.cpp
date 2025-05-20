#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Definimos los colores de las cartas como constantes para facilitar su uso
const string COLOR_ROJO = "Rojo";
const string COLOR_AZUL = "Azul";
const string COLOR_VERDE = "Verde";
const string COLOR_MORADO = "Morado";
const string COLOR_CAFE = "Cafe";
const string COLOR_NARANJA = "Naranja";

// Clase para representar una carta
class Carta {
private:
    string color;

public:
    // Constructor
    Carta(string _color) {
        color = _color;
    }

    // Método para obtener el color de la carta
    string getColor() {
        return color;
    }

    // Método para mostrar la carta
    void mostrar() {
        cout << "Carta de color " << color;
    }
};
