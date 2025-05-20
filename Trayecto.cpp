class Trayecto {
private:
    string origen;
    string destino;
    string colorNecesario;
    int longitud;
    bool completado;
    string jugadorQueCompleto;

public:
    // Constructor
    Trayecto(string _origen, string _destino, string _colorNecesario, int _longitud) {
        origen = _origen;
        destino = _destino;
        colorNecesario = _colorNecesario;
        longitud = _longitud;
        completado = false;
        jugadorQueCompleto = "";
    }
