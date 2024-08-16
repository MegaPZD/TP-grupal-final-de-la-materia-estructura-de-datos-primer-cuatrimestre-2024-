#ifndef AYED_TPG_1C2024_COORDENADA_HPP
#define AYED_TPG_1C2024_COORDENADA_HPP

#include <utility>

/* Esta clase es utilitaria:
 * Decora la clase std::pair para así tener nombres más adecuados para el TP,
 * manteniendo toda la funcionalidad ya implementada en la clase.
 * Esto incluye operadores como el ==, !=, <, constructores, entre otras cosas.
 * Para más información, ver este enlace: https://en.cppreference.com/w/cpp/utility/pair */

class coordenada : public std::pair<int, int> {
public:
    // Constructores.
    coordenada();

    coordenada(int x, int y);

    // Pre: -
    // Post: Devuelve la coordenada resultado de restar (esto implica {x1 - x2, y1 - y2}).
    coordenada operator-(coordenada coordenada1);

    // Pre: -
    // Post: Devuelve la coordenada x. Equivale a coordenada.first.
    int x();

    // Pre: -
    // Post: Devuelve la coordenada y. Equivale a coordenada.second.
    int y();
};

#endif