#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

// ======= Parte visual del tablero =======

struct Celda {
    char letra = ' ';
    string color = "";
};

map<string, string> ansiColor = {
    {"rojo", "\033[41m   \033[0m"},
    {"azul", "\033[44m   \033[0m"},
    {"verde", "\033[42m   \033[0m"},
    {"morado", "\033[45m   \033[0m"},
    {"cafe", "\033[48;5;94m   \033[0m"},
    {"naranja", "\033[48;5;208m   \033[0m"},
    {"blanco", "\033[47m   \033[0m"}
};

const int FILAS = 15;
const int COLS = 19;

map<char, pair<int, int>> letras = {
    {'A', {7, 0}},  {'B', {4, 2}},  {'C', {13, 2}}, {'D', {0, 3}}, {'E', {3, 5}},
    {'F', {7, 5}},  {'G', {11, 5}}, {'H', {7, 8}},  {'I', {4, 9}}, {'J', {1, 10}},
    {'K', {7,11}},  {'L', {11,11}}, {'M', {13,12}}, {'N', {1,13}}, {'O', {3,15}},
    {'P', {7,15}},  {'Q', {11,15}}, {'R', {5,18}},  {'S', {9,18}}
};

struct RutaVisual {
    pair<int, int> inicio;
    pair<int, int> fin;
    string color;
};

vector<RutaVisual> rutasVisuales = {
    {{7,1}, {7,4}, "azul"},       // A-F
    {{7,5}, {7,8}, "naranja"},   // F-H
    {{7,8}, {7,10}, "azul"},     // H-K
    {{6,0}, {4,0}, "rojo"},      // B-A
    {{4,1}, {4,1}, "rojo"},
    {{0,4}, {0,5}, "cafe"},      // D-E
    {{0,5}, {3,5}, "cafe"},
    {{12,2}, {11,2}, "cafe"},
    {{11,2}, {11,4}, "cafe"},
    {{4,5}, {6,5}, "verde"},     // E-F
    {{8,5}, {10,5}, "naranja"},  // F-G
    {{8,8}, {11,8}, "rojo"},     // H-L
    {{11,8}, {11,10}, "rojo"},
    {{5,9}, {5,11}, "morado"},   // I-K
    {{5,11}, {6,11}, "morado"},
    {{7,12}, {7,14}, "verde"},   // K-P
    {{8,15}, {10,15}, "verde"},  // P-Q
    {{11,16}, {11,18}, "cafe"},  // Q-S
    {{11,18}, {10,18}, "cafe"},
    {{13,13}, {13,15}, "morado"},
    {{13,15}, {12,15}, "morado"},
    {{3,16}, {3,18}, "morado"},  // O-R
    {{3,18}, {4,18}, "morado"},
    {{1,14}, {1,15}, "verde"},   // N-O
    {{1,15}, {2,15}, "verde"},
    {{1,11}, {1,12}, "rojo"},    // J-N
    {{4,15}, {6,15}, "naranja"}, // O-P
    {{8,11}, {11,11}, "naranja"},// K-L
    {{3,9}, {3,14}, "azul"}      // I-O
};

class TableroVisual {
private:
    vector<vector<Celda>> tablero;

public:
    TableroVisual() {
        inicializar();
    }

    void inicializar() {
        Celda vacia;
        vacia.letra = ' ';
        vacia.color = "blanco";
        tablero = vector<vector<Celda>>(FILAS, vector<Celda>(COLS, vacia));

        for (const auto& it : letras) {
            tablero[it.second.first][it.second.second].letra = it.first;
        }

        for (const auto& r : rutasVisuales) {
            int x1 = r.inicio.first, y1 = r.inicio.second;
            int x2 = r.fin.first, y2 = r.fin.second;
            string color = r.color;

            if (x1 == x2) {
                for (int y = min(y1, y2); y <= max(y1, y2); ++y)
                    tablero[x1][y].color = color;
            } else if (y1 == y2) {
                for (int x = min(x1, x2); x <= max(x1, x2); ++x)
                    tablero[x][y1].color = color;
            } else {
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

    void mostrar() const {
        cout << "    ";
        for (int c = 0; c < COLS; ++c) {
            if (c % 5 == 0)
                cout << setw(3) << c << " ";
            else
                cout << "    ";
        }
        cout << "\n";

        for (int i = 0; i < FILAS; ++i) {
            cout << setw(2) << i << " |";
            for (int j = 0; j < COLS; ++j) {
                const Celda& celda = tablero[i][j];
                if (celda.letra != ' ') {
                    cout << "\033[47;30m " << celda.letra << " \033[0m";
                } else {
                    cout << ansiColor[celda.color];
                }
            }
            cout << endl;
        }
    }
};

// ========== Aquí continuaríamos integrando las clases del juego ==========

int main() {
    TableroVisual tablero;
    tablero.mostrar();
    // Aquí continuarías integrando la lógica del juego que ya tienes.
    return 0;
}