#ifndef TABLERO_VISUAL_H
#define TABLERO_VISUAL_H

#include <vector>
#include <string>
#include "Reglas.h"
using namespace std;

class TableroVisual {
private:
    vector<vector<Celda>> tablero;

public:
    // Constructor
    TableroVisual();
    
    // Método para inicializar el tablero
    void inicializar();
    
    // Marcar una ruta completa (todos sus segmentos) como completada por un jugador
    void marcarRutaCompletada(string origen, string destino, int jugador);
    
    // Mostrar el tablero en la consola
    void mostrar() const;
};

#endif
