#include "Jugador.h"
#include "Reglas.h"
#include <iostream>
using namespace std;

// Constructor
Jugador::Jugador(string _nombre, int _numero) {
    nombre = _nombre;
    numero = _numero;
    vagonesDisponibles = 18; // Cada jugador empieza con 18 vagones
    
    // Inicializamos el mapa de cartas con 0 cartas de cada color
    cartas[COLOR_ROJO] = 0;
    cartas[COLOR_AZUL] = 0;
    cartas[COLOR_VERDE] = 0;
    cartas[COLOR_MORADO] = 0;
    cartas[COLOR_CAFE] = 0;
    cartas[COLOR_NARANJA] = 0;
}

// Método para obtener el nombre del jugador
string Jugador::getNombre() {
    return nombre;
}

// Método para obtener el número del jugador
int Jugador::getNumero() {
    return numero;
}

// Método para obtener la cantidad de vagones disponibles
int Jugador::getVagonesDisponibles() {
    return vagonesDisponibles;
}

// Método para añadir una carta a la mano del jugador
void Jugador::recibirCarta(Carta carta) {
    string color = carta.getColor();
    cartas[color]++; // Incrementamos el contador de cartas de ese color
    cout << nombre << " recibe una carta " << color << endl;
}

// Método para verificar si el jugador puede completar un trayecto
bool Jugador::puedeCompletarTrayecto(Trayecto trayecto) {
    string colorNecesario = trayecto.getColorNecesario();
    int cantidadNecesaria = trayecto.getLongitud();
    
    // Verificamos si el jugador tiene suficientes cartas del color necesario
    return cartas[colorNecesario] >= cantidadNecesaria;
}

// Método para completar un trayecto
bool Jugador::completarTrayecto(Trayecto &trayecto) {
    if (!puedeCompletarTrayecto(trayecto)) {
        cout << "No tienes suficientes cartas para completar este trayecto." << endl;
        return false;
    }
    
    // Reducimos los vagones disponibles
    vagonesDisponibles -= trayecto.getLongitud();
    
    // Reducimos las cartas usadas
    string colorNecesario = trayecto.getColorNecesario();
    cartas[colorNecesario] -= trayecto.getLongitud();
    
    // Marcamos el trayecto como completado
    trayecto.marcarComoCompletado(nombre, numero);
    
    // Añadimos el trayecto a los completados
    trayectosCompletados.push_back(trayecto);
    
    cout << nombre << " ha completado el trayecto de " 
         << trayecto.getOrigen() << " a " << trayecto.getDestino() << endl;
    
    return true;
}

// Método para calcular la puntuación total
int Jugador::calcularPuntuacion() {
    int puntuacion = 0;
    for (int i = 0; i < trayectosCompletados.size(); i++) {
        puntuacion += trayectosCompletados[i].calcularPuntos();
    }
    return puntuacion;
}

// Método para mostrar las cartas del jugador
void Jugador::mostrarCartas() {
    cout << "Cartas de " << nombre << ":" << endl;
    for (map<string, int>::iterator it = cartas.begin(); it != cartas.end(); it++) {
        cout << "  " << it->first << ": " << it->second << endl;
    }
}

// Método para mostrar los trayectos completados
void Jugador::mostrarTrayectosCompletados() {
    cout << "Trayectos completados por " << nombre << ":" << endl;
    for (int i = 0; i < trayectosCompletados.size(); i++) {
        cout << "  ";
        trayectosCompletados[i].mostrar();
        cout << " - " << trayectosCompletados[i].calcularPuntos() << " puntos" << endl;
    }
}
