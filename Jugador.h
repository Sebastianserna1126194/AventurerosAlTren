#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <map>
#include <vector>
#include "Carta.h"
#include "Trayecto.h"
using namespace std;

class Jugador {
private:
    string nombre;
    int vagonesDisponibles;
    int numero; // Número del jugador (1-4)
    // Usamos un mapa para contar cuántas cartas de cada color tiene el jugador
    map<string, int> cartas;
    // Vector para guardar los trayectos completados
    vector<Trayecto> trayectosCompletados;

public:
    // Constructor
    Jugador(string _nombre, int _numero);
    
    // Método para obtener el nombre del jugador
    string getNombre();
    
    // Método para obtener el número del jugador
    int getNumero();
    
    // Método para obtener la cantidad de vagones disponibles
    int getVagonesDisponibles();
    
    // Método para añadir una carta a la mano del jugador
    void recibirCarta(Carta carta);
    
    // Método para verificar si el jugador puede completar un trayecto
    bool puedeCompletarTrayecto(Trayecto trayecto);
    
    // Método para completar un trayecto
    bool completarTrayecto(Trayecto &trayecto);
    
    // Método para calcular la puntuación total
    int calcularPuntuacion();
    
    // Método para mostrar las cartas del jugador
    void mostrarCartas();
    
    // Método para mostrar los trayectos completados
    void mostrarTrayectosCompletados();
};

#endif
