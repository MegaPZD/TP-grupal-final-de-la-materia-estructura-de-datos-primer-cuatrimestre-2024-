#ifndef AYED_TPG_1C2024_VERTICE_HPP
#define AYED_TPG_1C2024_VERTICE_HPP

#include "coordenada.hpp"

class a_estrella;

class vertice {
private:
    coordenada posicion;
    vertice* padre;
    int costo_origen;
    int distancia_destino;

    // Constructores.
    vertice();

    vertice(coordenada posicion);

    vertice(coordenada posicion, vertice* padre);

    /* Esto permite que solamente a_estrella cree vértices y pueda acceder a sus atributos (evitando setters y getters).
     * Esto rompe encapsulamiento, pero es apropiado en este caso porque las clases están altamente acopladas. */
    friend class a_estrella;

public:
    /* Estos operadores están como públicos para que puedan definir la heuristica por fuera de la clase a_estrella.
     * De ser necesario, pueden agregar otros. Consulten por Slack si tienen dudas. */

    // Pre: -
    // Post: Devuelve true si el vértice tiene menor distancia al destino.
    bool operator<(const vertice& vertice1);

    // Pre: -
    // Post: Devuelve true si los vértices tienen la misma posición.
    bool operator==(const vertice& vertice1) const;

    // Pre: -
    // Post: Devuelve true si el vértice tiene la posición indicada.
    bool operator==(const coordenada& posicion1) const;

    // Pre: -
    // Post: Devuelve la posición resultado de restar las coordenadas de ambos vértices.
    coordenada operator-(const vertice& vertice1);

    // Pre: Los punteros no pueden ser nulos.
    // Post: Devuelve el resultado de ejecutar el operador < sobre los vértices desreferenciados.
    static bool menor(vertice* vertice1, vertice* vertice2);

    // Pre: Los punteros no pueden ser nulos.
    // Post: Devuelve el resultado de ejecutar el operador == sobre los vértices desreferenciados.
    static bool igual(vertice* vertice1, vertice* vertice2);
};

#endif