#ifndef CARTA_H
#define CARTA_H

#include <string>
using namespace std;

class Carta {
private:
    string color;

public:
    // Constructor
    Carta(string _color);
    
    // Método para obtener el color de la carta
    string getColor();
    
    // Método para mostrar la carta
    void mostrar();
};

#endif
