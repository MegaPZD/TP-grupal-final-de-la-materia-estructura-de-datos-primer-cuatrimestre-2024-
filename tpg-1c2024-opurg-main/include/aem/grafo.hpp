#ifndef AYED_TPG_1C2024_GRAFO_HPP
#define AYED_TPG_1C2024_GRAFO_HPP

#include <vector>
#include "matriz.hpp"
#include "arista.hpp"

// Usen un valor suficientemente grande para no tener problemas.
// También, pueden usar un valor negativo.
const int INFINITO = 999;

// Este grafo va a calcular el arbol de expansión mínimo/máximo (MST).
class grafo {
private:
    matriz<int> matriz_adyacencia;
public:
    // Constructores.
    grafo() = default;

    grafo(size_t cantidad_vertices);

    // Pre: -
    // Post: Agrega un nuevo vértice aislado al grafo (es decir, no tiene ninguna arista asociada).
    // NOTA: El número del vértice corresponde con el último índice agregado a la matriz.
    // Por ejemplo, si tienen 5 vértices y se agrega uno más, ese vértice es el 5 (recordar que matriz es 0-indexed).
    void agregar_vertice();

    // Pre: -
    // Post: Agrega (o modifica) la arista desde origen a destino. Si los vértices no son válidos, la matriz no cambia.
    // NOTA: Como solo se guarda una arista entre dos vértices, este grafo no puede tener aristas paralelas.
    void modificar_arista(size_t origen, size_t destino, int peso);

    // Pre: -
    // Post: Elimina la arista desde origen a destino. Si los vértices no son válidos, la matriz no cambia.
    void eliminar_arista(size_t origen, size_t destino);

    // Pre: -
    // Post: Aisla el vértice. Si no es válido, la matriz no cambia.
    void aislar_vertice(size_t vertice);

    // Constructor de copia.
    grafo(const grafo& grafo1);

    // Operador de asignación.
    grafo& operator=(const grafo& grafo1);

    // Pre: El grafo representado debe ser conexo y no direccionado (asumirlo).
    // Post: Devuelve el arbol de expansión mínimo/máximo.
    std::vector<arista> obtener_aem();
};

#endif