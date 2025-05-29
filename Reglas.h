#ifndef REGLAS_H
#define REGLAS_H

#include <string>
#include <map>
#include <vector>
using namespace std;

// Definimos los colores de las cartas como constantes
extern const string COLOR_ROJO;
extern const string COLOR_AZUL;
extern const string COLOR_VERDE;
extern const string COLOR_MORADO;
extern const string COLOR_CAFE;
extern const string COLOR_NARANJA;

// Constantes del tablero
extern const int FILAS;
extern const int COLS;

// Estructura para las celdas del tablero
struct Celda {
    char letra = ' ';
    string color = "";
    int jugador = 0; // 0 = sin jugador, 1-4 = jugador que completó la ruta
};

// Estructura para definir una ruta visual en el tablero
struct RutaVisual {
    pair<int, int> inicio;
    pair<int, int> fin;
    string color;
    string origen;
    string destino;
    string idTrayecto;
};

// Variables globales
extern map<string, string> ansiColor;
extern map<char, pair<int, int>> letras;
extern vector<RutaVisual> rutasVisuales;
extern map<string, vector<RutaVisual>> mapaTrayectos;

#endif
