#ifndef AYED_TPG_1C2024_A_ESTRELLA_HPP
#define AYED_TPG_1C2024_A_ESTRELLA_HPP

#include <vector>
#include <stack>
#include "vertice.hpp"
#include "mapa.hpp"
#include <random>

class a_estrella {
private:
    std::vector<vertice*> set_abierto;
    std::vector<vertice*> set_cerrado;

    // Pre: -
    // Post: Devuelve el vértice con menor distancia al destino, quitándolo del set abierto.
    // Si el set abierto está vacío, devuelve nullptr.
    vertice* buscar_mejor_vertice();

    // Pre: -
    // Post: Busca y devuelve, de existir, el vértice con la posición indicada.
    // Si no existe (o el set está vacío), devuelve nullptr.
    vertice* buscar_vertice(std::vector<vertice*> set, coordenada posicion);

    // Pre: -
    // Post: Limpia los sets, liberando la memoria reservada para los vértices.
    // NOTA: Es necesario limpiarlos entre llamados a obtener_camino_minimo.
    void limpiar_sets();

    // Pre: Se debe haber encontrado el vértice destino
    // (es decir, destino está correctamente conectado con los vértices desde el origen).
    // Post: Devuelve el camino encontrado desde el origen hasta el destino.
    std::stack<coordenada> reconstruir_camino(vertice* destino);

    // Pre: Los vertices deben ser vecinos
    // Post: Se devuelve el costo de ir de actual a vecino, teniendo en cuenta la heurística proporcionada
    int calcular_costo(vertice* actual, vertice* vecino, vertice* destino, int costo_origen, int (*heuristica)(vertice* destino, vertice* actual));

public:

    // Pre: -
    // Post: Devuelve el camino encontrado desde el origen hasta el destino.
    // De no haber camino, devuelve un camino vacío.
    // NOTA: Si manejan bien desde mapa la validez de un vecino, origen y destino podrían ser coordenadas no válidas.
    // Sin embargo, probablemente les convenga revisar de antemano si tiene sentido la búsqueda.
    std::stack<coordenada> obtener_camino_minimo(coordenada origen, coordenada destino, mapa& mapa_callejon, int (*heuristica)(vertice* destino, vertice* actual));
};

#endif