#include "TableroVisual.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

// Constructor
TableroVisual::TableroVisual() {
    inicializar();
    
    // Inicializar el mapa de trayectos
    for (const auto& ruta : rutasVisuales) {
        mapaTrayectos[ruta.idTrayecto].push_back(ruta);
    }
}

void TableroVisual::inicializar() {
    // Inicializar el tablero con celdas vacías
    Celda vacia;
    vacia.letra = ' ';
    vacia.color = "blanco";
    tablero = vector<vector<Celda>>(FILAS, vector<Celda>(COLS, vacia));

    // Colocar las letras (ciudades) en el tablero
    for (const auto& it : letras) {
        tablero[it.second.first][it.second.second].letra = it.first;
    }

    // Dibujar las rutas en el tablero
    for (const auto& r : rutasVisuales) {
        int x1 = r.inicio.first, y1 = r.inicio.second;
        int x2 = r.fin.first, y2 = r.fin.second;
        string color = r.color;

        if (x1 == x2) {
            // Ruta horizontal
            for (int y = min(y1, y2); y <= max(y1, y2); ++y)
                tablero[x1][y].color = color;
        } else if (y1 == y2) {
            // Ruta vertical
            for (int x = min(x1, x2); x <= max(x1, x2); ++x)
                tablero[x][y1].color = color;
        } else {
            // Ruta diagonal
            int dx = (x2 > x1) ? 1 : -1;
            int dy = (y2 > y1) ? 1 : -1;
            int x = x1, y = y1;
            while (x != x2 || y != y2) {
                tablero[x][y].color = color;
                if (x != x2) x += dx;
                if (y != y2) y += dy;
            }
            tablero[x2][y2].color = color;
        }
    }
}

// Marcar una ruta completa (con todos sus segmentos) como completada por un jugador
void TableroVisual::marcarRutaCompletada(string origen, string destino, int jugador) {
    // Construimos el identificador del trayecto (tanto en un sentido como en el otro)
    string idTrayecto1 = origen + "-" + destino;
    string idTrayecto2 = destino + "-" + origen;
    
    // Buscamos el trayecto en el mapa (considerando ambas direcciones)
    auto it = mapaTrayectos.find(idTrayecto1);
    if (it == mapaTrayectos.end()) {
        it = mapaTrayectos.find(idTrayecto2);
    }
    
    if (it != mapaTrayectos.end()) {
        // Recorremos todos los segmentos de este trayecto
        for (const auto& r : it->second) {
            int x1 = r.inicio.first, y1 = r.inicio.second;
            int x2 = r.fin.first, y2 = r.fin.second;
            
            if (x1 == x2) {
                // Ruta horizontal
                for (int y = min(y1, y2); y <= max(y1, y2); ++y) {
                    tablero[x1][y].color = "jugador" + to_string(jugador);
                    tablero[x1][y].jugador = jugador;
                }
            } else if (y1 == y2) {
                // Ruta vertical
                for (int x = min(x1, x2); x <= max(x1, x2); ++x) {
                    tablero[x][y1].color = "jugador" + to_string(jugador);
                    tablero[x][y1].jugador = jugador;
                }
            } else {
                // Ruta diagonal
                int dx = (x2 > x1) ? 1 : -1;
                int dy = (y2 > y1) ? 1 : -1;
                int x = x1, y = y1;
                while (x != x2 || y != y2) {
                    tablero[x][y].color = "jugador" + to_string(jugador);
                    tablero[x][y].jugador = jugador;
                    if (x != x2) x += dx;
                    if (y != y2) y += dy;
                }
                tablero[x2][y2].color = "jugador" + to_string(jugador);
                tablero[x2][y2].jugador = jugador;
            }
        }
    }
}

// Mostrar el tablero en la consola
void TableroVisual::mostrar() const {
    cout << "\n=== TABLERO DEL JUEGO  ===\n\n";
    
    // Mostrar números de columna
    cout << "    ";
    for (int c = 0; c < COLS; ++c) {
        if (c % 5 == 0)
            cout << setw(3) << c << " ";
        else
            cout << "    ";
    }
    cout << "\n";

    // Mostrar el tablero
    for (int i = 0; i < FILAS; ++i) {
        cout << setw(2) << i << " |";
        for (int j = 0; j < COLS; ++j) {
            const Celda& celda = tablero[i][j];
            
            if (celda.letra != ' ') {
                // Es una ciudad (letra) - mostrar con fondo blanco y texto negro
                cout << "\033[47;30m " << celda.letra << " \033[0m";
            } else if (celda.jugador > 0) {
                // Es una ruta completada por un jugador - mostrar número del jugador con color de fondo
                if (celda.jugador == 1) {
                    cout << "\033[48;5;196;30m " << celda.jugador << " \033[0m"; // Rojo
                } else if (celda.jugador == 2) {
                    cout << "\033[48;5;21;37m " << celda.jugador << " \033[0m";  // Azul
                } else if (celda.jugador == 3) {
                    cout << "\033[48;5;46;30m " << celda.jugador << " \033[0m";  // Verde
                } else if (celda.jugador == 4) {
                    cout << "\033[48;5;226;30m " << celda.jugador << " \033[0m"; // Amarillo
                }
            } else {
                // Es una ruta sin completar o espacio vacío - mostrar color original
                cout << ansiColor[celda.color];
            }
        }
        cout << endl;
    }
    
    // Mostrar leyenda
    cout << "\nMENU PRINCIPAL:\n";
    cout << "Ciudades: A-S (con fondo blanco)\n";
    cout << "Rutas disponibles: " << ansiColor["rojo"] << " Rojo, " 
         << ansiColor["azul"] << " Azul, " 
         << ansiColor["verde"] << " Verde, " 
         << ansiColor["morado"] << " Morado, " 
         << ansiColor["cafe"] << " Cafe, " 
         << ansiColor["naranja"] << " Naranja\n";
    cout << "Rutas completadas: " 
         << "\033[48;5;196;30m 1 \033[0m Jugador 1, " 
         << "\033[48;5;21;37m 2 \033[0m Jugador 2, " 
         << "\033[48;5;46;30m 3 \033[0m Jugador 3, " 
         << "\033[48;5;226;30m 4 \033[0m Jugador 4\n";
}
