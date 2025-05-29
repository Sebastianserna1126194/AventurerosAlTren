#include "Trayecto.h"
#include <iostream>
using namespace std;

// Constructor
Trayecto::Trayecto(string _origen, string _destino, string _colorNecesario, int _longitud) {
    origen = _origen;
    destino = _destino;
    colorNecesario = _colorNecesario;
    longitud = _longitud;
    completado = false;
    jugadorQueCompleto = "";
    numeroJugador = 0;
}

// Métodos para obtener información del trayecto
string Trayecto::getOrigen() { return origen; }
string Trayecto::getDestino() { return destino; }
string Trayecto::getColorNecesario() { return colorNecesario; }
int Trayecto::getLongitud() { return longitud; }
bool Trayecto::estaCompletado() { return completado; }
string Trayecto::getJugadorQueCompleto() { return jugadorQueCompleto; }
int Trayecto::getNumeroJugador() { return numeroJugador; }

// Método para marcar el trayecto como completado
void Trayecto::marcarComoCompletado(string nombreJugador, int numJugador) {
    completado = true;
    jugadorQueCompleto = nombreJugador;
    numeroJugador = numJugador;
}

// Método para calcular los puntos que da este trayecto
int Trayecto::calcularPuntos() {
    // Según las reglas del juego
    if (longitud == 2) return 1;
    if (longitud == 3) return 2;
    if (longitud == 4) return 4;
    if (longitud == 5) return 6;
    if (longitud == 6) return 9;
    return 0; // Por si acaso hay un trayecto de longitud diferente
}

// Método para mostrar el trayecto
void Trayecto::mostrar() {
    cout << "Trayecto de " << origen << " a " << destino 
         << " (Longitud: " << longitud << ", Color: " << colorNecesario << ")";
    
    if (completado) {
        cout << " - Completado por " << jugadorQueCompleto;
    }
}
