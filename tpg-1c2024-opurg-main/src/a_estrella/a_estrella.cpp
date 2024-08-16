#include "a_estrella.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>

vertice* a_estrella::buscar_mejor_vertice() {
    vertice* mejor_vertice = nullptr;
    auto it = min_element(set_abierto.begin(), set_abierto.end(), vertice::menor);
    if (it != set_abierto.end()) {
        mejor_vertice = *it;
        set_abierto.erase(it);
    }
    return mejor_vertice;
}

vertice* a_estrella::buscar_vertice(std::vector<vertice*> set, coordenada posicion) {
    vertice* vertice_buscado = nullptr;
    auto coincide_posicion = [&posicion](vertice* v) { return *v == posicion; };
    auto it = std::find_if(set.begin(), set.end(), coincide_posicion);
    if (it != set.end()) {
        vertice_buscado = *it;
    }
    return vertice_buscado;
}

void a_estrella::limpiar_sets() {
    for (vertice* vertice: set_abierto) {
        delete vertice;
    }
    for (vertice* vertice: set_cerrado) {
        delete vertice;
    }
    set_abierto.clear();
    set_cerrado.clear();
}

std::stack<coordenada> a_estrella::reconstruir_camino(vertice* destino) {
    std::stack<coordenada> camino;
    vertice* actual = destino;

    while (actual != nullptr){
        camino.push(actual->posicion);
        actual = actual->padre;
    }
    return camino;
}


int a_estrella::calcular_costo(vertice* actual, vertice* vecino, vertice* destino, int costo_origen, int (*heuristica)(vertice* destino, vertice* actual)) {
    // Costo desde el origen hasta el vecino, "caminar"
    int nuevo_costo_origen = costo_origen + 1;  // Costo 1, como base

    // Heurística: Distancia estimada desde el vecino hasta el destino usando la función heurística proporcionada
    int heuristica_vecino_destino = heuristica(destino, vecino);

    int costo_total = nuevo_costo_origen + heuristica_vecino_destino;

    // Me muevo al vecino
    if (vecino->padre == nullptr || nuevo_costo_origen < vecino->costo_origen) {
        vecino->costo_origen = nuevo_costo_origen;
        vecino->distancia_destino = heuristica_vecino_destino;
        vecino->padre = actual;
    }

    return costo_total;
}

std::stack<coordenada> a_estrella::obtener_camino_minimo(coordenada origen, coordenada destino, mapa& mapa_callejon,
                                                         int (*heuristica)(vertice* destino, vertice* actual)) {
    
    set_cerrado.clear();
    // Limpiar conjuntos abiertos y cerrados, en cada búsqueda
    limpiar_sets();
    // Crear vértice de origen/inicial y destino/final
    vertice* inicio = new vertice(origen);
    vertice* final = new vertice(destino);

    // Agrego el inicio a los vertices (casilla) no visitados
    set_abierto.push_back(inicio);
    // Variables en duda
    bool encontrado = false;
    std::stack<coordenada> camino;

    while(!set_abierto.empty() && !encontrado){
        // El vertice actual, será el más cercano al vertice final (destino)
        vertice* actual = buscar_mejor_vertice();

        // Muevo el actual a los visitados
        set_cerrado.push_back(actual);
        // Condicional si llegamos a destino
        if (*actual == *final){
            camino = reconstruir_camino(actual);
            delete inicio;
            delete final;
            encontrado = true;
        }

        // Generar los vecinos_validos (CAMINABLES) del actual
        std::vector<coordenada> vecinos_validos = mapa_callejon.obtener_vecinos_validos(actual->posicion, destino);

        for (auto& vecino_pos : vecinos_validos) {
            vertice* vecino_actual = new vertice(vecino_pos, actual);
            bool esta_en_cerrado = std::any_of(set_cerrado.begin(), set_cerrado.end(), [&](auto& v) { return vertice::igual(v, vecino_actual); });

            if (!esta_en_cerrado) {
                auto it_abierto = std::find_if(set_abierto.begin(), set_abierto.end(), [&](auto& v) { return vertice::igual(v, vecino_actual); });
                int nuevo_costo_origen = actual->costo_origen + 1;

                if (it_abierto == set_abierto.end()) {
                    set_abierto.push_back(vecino_actual);
                    vecino_actual->padre = actual;
                } else {
                    if (nuevo_costo_origen < (*it_abierto)->costo_origen) {
                        calcular_costo(actual, *it_abierto, final, actual->costo_origen, heuristica);
                    }
                }
            } else {
                delete vecino_actual;
            }
        }
    }
    return camino;
}
