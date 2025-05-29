#include "Reglas.h"

// Definición de constantes
const string COLOR_ROJO = "rojo";
const string COLOR_AZUL = "azul";
const string COLOR_VERDE = "verde";
const string COLOR_MORADO = "morado";
const string COLOR_CAFE = "cafe";
const string COLOR_NARANJA = "naranja";

const int FILAS = 15;
const int COLS = 19;

// Definición de variables globales
map<string, string> ansiColor = {
    {"rojo", "\033[41m   \033[0m"},
    {"azul", "\033[44m   \033[0m"},
    {"verde", "\033[42m   \033[0m"},
    {"morado", "\033[45m   \033[0m"},
    {"cafe", "\033[48;5;94m   \033[0m"},
    {"naranja", "\033[48;5;208m   \033[0m"},
    {"blanco", "\033[47m   \033[0m"},
    {"jugador1", "\033[48;5;196m   \033[0m"},
    {"jugador2", "\033[48;5;21m   \033[0m"},
    {"jugador3", "\033[48;5;46m   \033[0m"},
    {"jugador4", "\033[48;5;226m   \033[0m"}
};

map<char, pair<int, int>> letras = {
    {'A', {7, 0}},  {'B', {4, 2}},  {'C', {13, 2}}, {'D', {0, 3}}, {'E', {3, 5}},
    {'F', {7, 5}},  {'G', {11, 5}}, {'H', {7, 8}},  {'I', {4, 9}}, {'J', {1, 10}},
    {'K', {7,11}},  {'L', {11,11}}, {'M', {13,12}}, {'N', {1,13}}, {'O', {3,15}},
    {'P', {7,15}},  {'Q', {11,15}}, {'R', {5,18}},  {'S', {9,18}}
};

vector<RutaVisual> rutasVisuales = {
    {{7,1}, {7,4}, "azul", "A", "F", "A-F"},
    {{7,5}, {7,8}, "naranja", "F", "H", "F-H"},
    {{7,8}, {7,10}, "azul", "H", "K", "H-K"},
    {{6,0}, {4,0}, "rojo", "A", "B", "A-B"},
    {{4,1}, {4,2}, "rojo", "A", "B", "A-B"},
    {{0,3}, {0,5}, "cafe", "D", "E", "D-E"},
    {{0,5}, {3,5}, "cafe", "D", "E", "D-E"},
    {{13,2}, {11,2}, "cafe", "C", "G", "C-G"},
    {{11,2}, {11,5}, "cafe", "C", "G", "C-G"},
    {{4,5}, {6,5}, "verde", "E", "F", "E-F"},
    {{8,5}, {10,5}, "naranja", "F", "G", "F-G"},
    {{8,8}, {11,8}, "rojo", "H", "L", "H-L"},
    {{11,8}, {11,11}, "rojo", "H", "L", "H-L"},
    {{5,9}, {5,11}, "morado", "I", "K", "I-K"},
    {{5,11}, {6,11}, "morado", "I", "K", "I-K"},
    {{7,12}, {7,14}, "verde", "K", "P", "K-P"},
    {{8,15}, {10,15}, "verde", "P", "Q", "P-Q"},
    {{11,16}, {11,18}, "cafe", "Q", "S", "Q-S"},
    {{11,18}, {9,18}, "cafe", "Q", "S", "Q-S"},
    {{13,13}, {13,15}, "morado", "M", "Q", "M-Q"},
    {{13,15}, {11,15}, "morado", "M", "Q", "M-Q"},
    {{3,16}, {3,18}, "morado", "O", "R", "O-R"},
    {{3,18}, {5,18}, "morado", "O", "R", "O-R"},
    {{1,14}, {1,15}, "verde", "N", "O", "N-O"},
    {{1,15}, {3,15}, "verde", "N", "O", "N-O"},
    {{1,11}, {1,13}, "rojo", "J", "N", "J-N"},
    {{4,15}, {6,15}, "naranja", "O", "P", "O-P"},
    {{8,11}, {11,11}, "naranja", "K", "L", "K-L"},
    {{4,9}, {3,9}, "azul", "I", "O", "I-O"},
    {{3,9}, {3,14}, "azul", "I", "O", "I-O"}
};

map<string, vector<RutaVisual>> mapaTrayectos;
