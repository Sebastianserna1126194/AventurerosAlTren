#include <iostream>
#include <vector>
#include <string>
#include "JuegoTrenes.h"
using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "¡BIENVENIDO AL JUEGO AVENTUREROS AL TREN!" << endl;
    cout << "========================================" << endl;
    
    // Preguntamos cuántos jugadores van a jugar
    int numJugadores;
    do {
        cout << "¿Cuántos jugadores van a jugar? (2-4): ";
        cin >> numJugadores;
        
        if (numJugadores < 2 || numJugadores > 4) {
            cout << "Solo se permiten entre 2 a 4 jugadores." << endl;
        }
    } while (numJugadores < 2 || numJugadores > 4);
    
    // Pedimos los nombres de los jugadores
    vector<string> nombresJugadores;
    for (int i = 1; i <= numJugadores; i++) {
        string nombre;
        cout << "Nombre del Jugador " << i << ": ";
        cin >> nombre;
        nombresJugadores.push_back(nombre);
    }
    
    // Creamos e iniciamos el juego
    JuegoTrenes juego(nombresJugadores);
    juego.jugarPartida();
    
    return 0;
}
