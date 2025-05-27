class Jugador {
private:
    string nombre;
    int vagonesDisponibles;
    // Usamos un mapa para contar cuántas cartas de cada color tiene el jugador
    map<string, int> cartas;
    // Vector para guardar los trayectos completados
    vector<Trayecto> trayectosCompletados;

public:
    // Constructor
    Jugador(string _nombre) {
        nombre = _nombre;
        vagonesDisponibles = 18; // Cada jugador empieza con 18 vagones
        
        // Inicializamos el mapa de cartas con 0 cartas de cada color
        cartas[COLOR_ROJO] = 0;
        cartas[COLOR_AZUL] = 0;
        cartas[COLOR_VERDE] = 0;
        cartas[COLOR_MORADO] = 0;
        cartas[COLOR_CAFE] = 0;
        cartas[COLOR_NARANJA] = 0;
    }
