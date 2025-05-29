#ifndef JUEGO_TRENES_H
#define JUEGO_TRENES_H

#include <vector>
#include <map>
#include <string>
#include "Jugador.h"
#include "Carta.h"
#include "Trayecto.h"
#include "TableroVisual.h"
using namespace std;

class JuegoTrenes {
private:
    vector<Jugador> jugadores;
    vector<Carta> mazo;
    vector<Carta> descarte;
    vector<Trayecto> trayectos;
    TableroVisual tablero;
    vector<Carta> cartasVisibles;
    int jugadorActual;
    bool juegoTerminado;
    bool ultimaRonda;
    int jugadorQueInicioUltimaRonda;

public:
    // Constructor
    JuegoTrenes(vector<string> nombresJugadores);
    
    // Método para barajar el mazo
    void barajarMazo();
    
    // Método para robar una carta del mazo
    Carta robarCartaDelMazo();
    
    // Método para que un jugador robe dos cartas de entre cuatro opciones
    void robarDosCartas();
    
    // Método para que un jugador complete un trayecto
    void completarTrayecto(int indiceTrayecto);
    
    // Método para verificar si el juego ha terminado
    void verificarFinJuego();
    
    // Método para mostrar los trayectos disponibles
    void mostrarTrayectosDisponibles();
    
    // Método para obtener el índice real de un trayecto disponible
    int getIndiceTrayectoDisponible(int indiceVisible);
    
    // Método para contar cuántos trayectos disponibles hay
    int contarTrayectosDisponibles();
    
    // Método para jugar una partida completa
    void jugarPartida();
    
    // Método para mostrar los resultados finales
    void mostrarResultados();
};

#endif
