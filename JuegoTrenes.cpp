#include "JuegoTrenes.h"
#include "Reglas.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

// Constructor
JuegoTrenes::JuegoTrenes(vector<string> nombresJugadores) {
    // Inicializamos el generador de números aleatorios
    srand(time(NULL));
    
    // Creamos los jugadores
    for (int i = 0; i < nombresJugadores.size(); i++) {
        jugadores.push_back(Jugador(nombresJugadores[i], i+1));
    }
    
    // Inicializamos el mazo con 12 cartas de cada color
    for (int i = 0; i < 12; i++) {
        mazo.push_back(Carta(COLOR_ROJO));
        mazo.push_back(Carta(COLOR_AZUL));
        mazo.push_back(Carta(COLOR_VERDE));
        mazo.push_back(Carta(COLOR_MORADO));
        mazo.push_back(Carta(COLOR_CAFE));
        mazo.push_back(Carta(COLOR_NARANJA));
    }
    
    // Barajamos el mazo
    barajarMazo();
    
    // Creamos los trayectos según el tablero visual proporcionado
    trayectos.push_back(Trayecto("A", "F", COLOR_AZUL, 4));
    trayectos.push_back(Trayecto("F", "H", COLOR_NARANJA, 2));
    trayectos.push_back(Trayecto("H", "K", COLOR_AZUL, 2));
    trayectos.push_back(Trayecto("A", "B", COLOR_ROJO, 4));
    trayectos.push_back(Trayecto("D", "E", COLOR_CAFE, 4));
    trayectos.push_back(Trayecto("J", "N", COLOR_ROJO, 2));
    trayectos.push_back(Trayecto("C", "G", COLOR_CAFE, 4));
    trayectos.push_back(Trayecto("E", "F", COLOR_VERDE, 3));
    trayectos.push_back(Trayecto("F", "G", COLOR_NARANJA, 3));
    trayectos.push_back(Trayecto("H", "L", COLOR_ROJO, 6));
    trayectos.push_back(Trayecto("I", "K", COLOR_MORADO, 4));
    trayectos.push_back(Trayecto("K", "P", COLOR_VERDE, 3));
    trayectos.push_back(Trayecto("P", "Q", COLOR_VERDE, 3));
    trayectos.push_back(Trayecto("Q", "S", COLOR_CAFE, 4));
    trayectos.push_back(Trayecto("M", "Q", COLOR_MORADO, 4));
    trayectos.push_back(Trayecto("O", "R", COLOR_MORADO, 4));
    trayectos.push_back(Trayecto("N", "O", COLOR_VERDE, 3));
    trayectos.push_back(Trayecto("O", "P", COLOR_NARANJA, 3));
    trayectos.push_back(Trayecto("K", "L", COLOR_NARANJA, 3));
    trayectos.push_back(Trayecto("I", "O", COLOR_AZUL, 6));
    
    // Inicializamos las cartas visibles (5 cartas al inicio)
    for (int i = 0; i < 5; i++) {
        cartasVisibles.push_back(robarCartaDelMazo());
    }
    
    // El primer jugador empieza
    jugadorActual = 0;
    juegoTerminado = false;
    ultimaRonda = false;
    jugadorQueInicioUltimaRonda = -1;
}

// Método para barajar el mazo
void JuegoTrenes::barajarMazo() {
    // Implementación simple de barajado
    for (int i = 0; i < mazo.size(); i++) {
        int j = rand() % mazo.size();
        swap(mazo[i], mazo[j]);
    }
}

// Método para robar una carta del mazo
Carta JuegoTrenes::robarCartaDelMazo() {
    // Si el mazo está vacío, barajamos el descarte
    if (mazo.empty()) {
        cout << "El mazo está vacío. Barajando el descarte..." << endl;
        mazo = descarte;
        descarte.clear();
        barajarMazo();
    }
    
    // Robamos la primera carta del mazo
    Carta carta = mazo.back();
    mazo.pop_back();
    return carta;
}

// Método para que un jugador robe dos cartas de entre cuatro opciones
void JuegoTrenes::robarDosCartas() {
    Jugador &jugador = jugadores[jugadorActual];
    
    cout << "\n" << jugador.getNombre() << " va a robar cartas." << endl;
    
    // Mostramos 4 cartas aleatorias para elegir
    vector<Carta> cartasDisponibles;
    cout << "Se muestran 4 cartas para elegir:" << endl;
    
    for (int i = 0; i < 4; i++) {
        Carta carta = robarCartaDelMazo();
        cartasDisponibles.push_back(carta);
        cout << i+1 << ". Carta de color " << carta.getColor() << endl;
    }
    
    // El jugador elige 2 cartas
    vector<int> selecciones;
    for (int i = 0; i < 2; i++) {
        int seleccion;
        do {
            cout << "Elige la carta " << (i+1) << " (1-4): ";
            cin >> seleccion;
            
            // Verificar que la selección sea válida y no haya sido elegida antes
            if (seleccion < 1 || seleccion > 4) {
                cout << "Selección inválida. Debe ser un número entre 1 y 4." << endl;
                continue;
            }
            
            // Verificar que no haya elegido esta carta antes
            if (find(selecciones.begin(), selecciones.end(), seleccion) != selecciones.end()) {
                cout << "Ya elegiste esta carta. Elige otra." << endl;
                continue;
            }
            
            // Selección válida
            break;
            
        } while (true);
        
        selecciones.push_back(seleccion);
    }
    
    // El jugador recibe las cartas seleccionadas
    for (int seleccion : selecciones) {
        jugador.recibirCarta(cartasDisponibles[seleccion-1]);
    }
    
    // Las cartas no seleccionadas van al descarte
    for (int i = 0; i < 4; i++) {
        if (find(selecciones.begin(), selecciones.end(), i+1) == selecciones.end()) {
            descarte.push_back(cartasDisponibles[i]);
            cout << "La carta de color " << cartasDisponibles[i].getColor() << " va al descarte." << endl;
        }
    }
    
    // Pasamos al siguiente jugador
    jugadorActual = (jugadorActual + 1) % jugadores.size();
    
    // Verificamos si el juego ha terminado
    verificarFinJuego();
}

// Método para que un jugador complete un trayecto
void JuegoTrenes::completarTrayecto(int indiceTrayecto) {
    Jugador &jugador = jugadores[jugadorActual];
    Trayecto &trayecto = trayectos[indiceTrayecto];
    
    // Verificamos si el trayecto ya está completado
    if (trayecto.estaCompletado()) {
        cout << "Este trayecto ya ha sido completado por otro jugador." << endl;
        return;
    }
    
    // Verificamos si el jugador puede completar el trayecto
    if (jugador.puedeCompletarTrayecto(trayecto)) {
        // El jugador completa el trayecto
        if (jugador.completarTrayecto(trayecto)) {
            // Actualizamos el tablero visual
            tablero.marcarRutaCompletada(trayecto.getOrigen(), trayecto.getDestino(), jugador.getNumero());
            
            cout << "\n¡Ruta completada! El tablero ahora muestra el número " << jugador.getNumero() 
                 << " en TODA la ruta de " << trayecto.getOrigen() << " a " << trayecto.getDestino() << endl;
            
            // Pasamos al siguiente jugador
            jugadorActual = (jugadorActual + 1) % jugadores.size();
            
            // Verificamos si el juego ha terminado
            verificarFinJuego();
        }
    } else {
        cout << "No puedes completar este trayecto. Te faltan cartas." << endl;
    }
}

// Método para verificar si el juego ha terminado
void JuegoTrenes::verificarFinJuego() {
    // Si ya estamos en la última ronda, verificamos si hemos vuelto al jugador que la inició
    if (ultimaRonda) {
        if (jugadorActual == jugadorQueInicioUltimaRonda) {
            juegoTerminado = true;
            cout << "¡Todos los jugadores han jugado su último turno! El juego ha terminado." << endl;
        }
        return;
    }
    
    // Verificamos si algún jugador tiene menos de 5 vagones
    for (int i = 0; i < jugadores.size(); i++) {
        if (jugadores[i].getVagonesDisponibles() < 5) {
            ultimaRonda = true;
            jugadorQueInicioUltimaRonda = jugadorActual;
            cout << "¡" << jugadores[i].getNombre() << " tiene menos de 5 vagones! El juego terminará después de esta ronda." << endl;
            break;
        }
    }
}

// Método para mostrar los trayectos disponibles
void JuegoTrenes::mostrarTrayectosDisponibles() {
    cout << "\nTRAYECTOS DISPONIBLES:" << endl;
    cout << "=====================" << endl;
    
    int contador = 1;
    for (int i = 0; i < trayectos.size(); i++) {
        if (!trayectos[i].estaCompletado()) {
            cout << contador << ". ";
            trayectos[i].mostrar();
            cout << endl;
            contador++;
        }
    }
    
    if (contador == 1) {
        cout << "No hay trayectos disponibles." << endl;
    }
}

// Método para obtener el índice real de un trayecto disponible
int JuegoTrenes::getIndiceTrayectoDisponible(int indiceVisible) {
    int contador = 0;
    for (int i = 0; i < trayectos.size(); i++) {
        if (!trayectos[i].estaCompletado()) {
            contador++;
            if (contador == indiceVisible) {
                return i;
            }
        }
    }
    return -1; // No encontrado
}

// Método para contar cuántos trayectos disponibles hay
int JuegoTrenes::contarTrayectosDisponibles() {
    int contador = 0;
    for (int i = 0; i < trayectos.size(); i++) {
        if (!trayectos[i].estaCompletado()) {
            contador++;
        }
    }
    return contador;
}

// Método para jugar una partida completa
void JuegoTrenes::jugarPartida() {
    cout << "¡Comienza el juego de trenes!" << endl;
    
    // Repartimos 4 cartas a cada jugador al inicio
    for (int i = 0; i < jugadores.size(); i++) {
        cout << "Repartiendo cartas iniciales a " << jugadores[i].getNombre() << "..." << endl;
        for (int j = 0; j < 4; j++) {
            jugadores[i].recibirCarta(robarCartaDelMazo());
        }
    }
    
    // Bucle principal del juego
    while (!juegoTerminado) {
        Jugador &jugador = jugadores[jugadorActual];
        
        cout << "\n========================================" << endl;
        cout << "TURNO DE " << jugador.getNombre() << " (Jugador " << jugador.getNumero() << ")" << endl;
        cout << "Vagones disponibles: " << jugador.getVagonesDisponibles() << endl;
        cout << "========================================" << endl;
        
        // Dibujamos el tablero
        tablero.mostrar();
        
        // Mostramos las cartas del jugador
        cout << "\n";
        jugador.mostrarCartas();
        
        // Mostramos los trayectos disponibles
        mostrarTrayectosDisponibles();
        
        // El jugador elige su acción
        int opcion;
        cout << "\n¿Qué quieres hacer?" << endl;
        cout << "1. Robar dos cartas" << endl;
        cout << "2. Completar un trayecto" << endl;
        cout << "Opción: ";
        cin >> opcion;
        
        if (opcion == 1) {
            robarDosCartas();
        } else if (opcion == 2) {
            // Verificamos si hay trayectos disponibles
            int trayectosDisponibles = contarTrayectosDisponibles();
            if (trayectosDisponibles == 0) {
                cout << "No hay trayectos disponibles para completar. Robando dos cartas automáticamente." << endl;
                robarDosCartas();
            } else {
                int indiceVisible;
                cout << "¿Qué trayecto quieres completar? (1-" << trayectosDisponibles << "): ";
                cin >> indiceVisible;
                
                if (indiceVisible >= 1 && indiceVisible <= trayectosDisponibles) {
                    int indiceReal = getIndiceTrayectoDisponible(indiceVisible);
                    completarTrayecto(indiceReal);
                } else {
                    cout << "Trayecto inválido. Perdiste tu turno." << endl;
                    jugadorActual = (jugadorActual + 1) % jugadores.size();
                }
            }
        } else {
            cout << "Opción inválida. Perdiste tu turno." << endl;
            jugadorActual = (jugadorActual + 1) % jugadores.size();
        }
        
        // Pausa para que el usuario pueda leer
        cout << "\nPresiona Enter para continuar...";
        cin.ignore();
        cin.get();
    }
    
    // Mostramos los resultados finales
    mostrarResultados();
}

// Método para mostrar los resultados finales
void JuegoTrenes::mostrarResultados() {
    cout << "\n========================================" << endl;
    cout << "FIN DEL JUEGO" << endl;
    cout << "========================================" << endl;
    
    // Dibujamos el tablero final
    tablero.mostrar();
    
    // Calculamos y mostramos la puntuación de cada jugador
    map<int, vector<string>> puntuaciones; // Mapa de puntuación -> nombres de jugadores
    
    cout << "\nRESULTADOS FINALES:" << endl;
    cout << "==================" << endl;
    
    for (int i = 0; i < jugadores.size(); i++) {
        Jugador &jugador = jugadores[i];
        int puntuacion = jugador.calcularPuntuacion();
        
        cout << "\n" << jugador.getNombre() << " (Jugador " << jugador.getNumero() << "):" << endl;
        jugador.mostrarTrayectosCompletados();
        cout << "Puntuación total: " << puntuacion << " puntos" << endl;
        
        puntuaciones[puntuacion].push_back(jugador.getNombre());
    }
    
    // Mostramos el ganador (o ganadores en caso de empate)
    cout << "\n========================================" << endl;
    if (!puntuaciones.empty()) {
        int maxPuntuacion = puntuaciones.rbegin()->first;
        vector<string> ganadores = puntuaciones[maxPuntuacion];
        
        if (ganadores.size() == 1) {
            cout << "¡" << ganadores[0] << " ha ganado con " << maxPuntuacion << " puntos!" << endl;
        } else {
            cout << "¡Empate! Los siguientes jugadores han empatado con " << maxPuntuacion << " puntos:" << endl;
            for (int i = 0; i < ganadores.size(); i++) {
                cout << "- " << ganadores[i] << endl;
            }
        }
    } else {
        cout << "No hay ganadores. ¡Todos perdieron!" << endl;
    }
    cout << "========================================" << endl;
}
