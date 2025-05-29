#ifndef TRAYECTO_H
#define TRAYECTO_H

#include <string>
using namespace std;

class Trayecto {
private:
    string origen;
    string destino;
    string colorNecesario;
    int longitud;
    bool completado;
    string jugadorQueCompleto;
    int numeroJugador;

public:
    // Constructor
    Trayecto(string _origen, string _destino, string _colorNecesario, int _longitud);
    
    // Métodos para obtener información del trayecto
    string getOrigen();
    string getDestino();
    string getColorNecesario();
    int getLongitud();
    bool estaCompletado();
    string getJugadorQueCompleto();
    int getNumeroJugador();
    
    // Método para marcar el trayecto como completado
    void marcarComoCompletado(string nombreJugador, int numJugador);
    
    // Método para calcular los puntos que da este trayecto
    int calcularPuntos();
    
    // Método para mostrar el trayecto
    void mostrar();
};

#endif
