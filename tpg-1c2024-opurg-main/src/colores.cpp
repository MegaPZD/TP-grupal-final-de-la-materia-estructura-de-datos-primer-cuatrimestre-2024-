#include "colores.hpp"
#include <iostream>

std::string colores::obtener_color_segun_tipo(tipo_casilla tipo) {
    switch (tipo) {
        case tipo_casilla::PARED: return BLANCO;
        case tipo_casilla::CAMINABLE: return VERDE;
        case tipo_casilla::LOCAL: return AZUL;
        case tipo_casilla::CLIENTE: return AMARILLO;
        case tipo_casilla::CAMINADO: return ROJO;
        default: return RESET;
    }
}

void colores::imprimir_casilla(const std::string& color) {
    std::cout << color << CUADRADO << " " << RESET;
}