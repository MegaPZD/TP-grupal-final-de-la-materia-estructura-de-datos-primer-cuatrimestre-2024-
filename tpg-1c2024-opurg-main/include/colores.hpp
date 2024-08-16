//
// Created by Khiber3000 on 5/27/2024.
//

#ifndef AYED_TPG_1C2024_COLORES_HPP
#define AYED_TPG_1C2024_COLORES_HPP

#include <string>
#include <vector>
#include "mapa.hpp"

#define ROJO     "\033[31m"
#define VERDE   "\033[32m"
#define AMARILLO  "\033[33m"
#define AZUL    "\033[34m"
#define BLANCO   "\033[37m"

const std::string CUADRADO = "\u2588";
const std::string RESET = "\033[0m";

class colores{
public:

    // Pre: -
    // Post: Según el tipo_casilla retorna el con string con el Unicode correspondiente
    // al tipo. Si es un tipo ínvalido retorna RESET ( que resetea al color default).
    static std::string obtener_color_segun_tipo(tipo_casilla tipo);

    // Pre: -
    // Post: Imprime un CUADRADO y, dependiendo del color, tendra diferente
    // coloración.
    static void imprimir_casilla(const std::string& color);

};

#endif //AYED_TPG_1C2024_COLORES_HPP