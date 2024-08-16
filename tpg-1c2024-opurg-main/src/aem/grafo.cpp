#include <iostream>
#include "grafo.hpp"

grafo::grafo(size_t cantidad_vertices) {
    matriz_adyacencia = matriz(cantidad_vertices, INFINITO);
    for (size_t i = 0; i < matriz_adyacencia.columnas(); i++) {
        matriz_adyacencia.elemento(i, i) = 0;
    }
}

void grafo::agregar_vertice() {
    size_t vertices = matriz_adyacencia.columnas() + 1;
    matriz_adyacencia.redimensionar(vertices, vertices);
    for (size_t i = 0; i < vertices - 1; i++) {
        eliminar_arista(vertices - 1, i);
        eliminar_arista(i, vertices - 1);
    }
}

void grafo::modificar_arista(size_t origen, size_t destino, int peso) {
    size_t vertices = matriz_adyacencia.columnas();
    if (origen < vertices && destino < vertices) {
        matriz_adyacencia.elemento(origen, destino) = peso;
    } else {
        std::cout << "ERROR: Los vértices no son válidos. No se cambió el camino." << std::endl;
    }
}

void grafo::eliminar_arista(size_t origen, size_t destino) {
    modificar_arista(origen, destino, INFINITO);
}

void grafo::aislar_vertice(size_t vertice) {
    size_t vertices = matriz_adyacencia.columnas();
    if (vertice < vertices) {
        for (size_t i = 0; i < vertices; i++) {
            if (i != vertice) {
                eliminar_arista(i, vertice);
                eliminar_arista(vertice, i);
            }
        }
    } else {
        std::cout << "ERROR: El vértice no es válido. No se aisló." << std::endl;
    }
}

grafo::grafo(const grafo& grafo1) {
    matriz_adyacencia = grafo1.matriz_adyacencia;
}

grafo& grafo::operator=(const grafo& grafo1) {
    if (this != &grafo1) {
        matriz_adyacencia = grafo1.matriz_adyacencia;
    }
    return *this;
}

std::vector<arista> grafo::obtener_aem() {
    std::vector<arista> aristas_maximas;
    std::vector<bool> vertices_visitados(matriz_adyacencia.columnas(), false);

    vertices_visitados[0] = true;
    size_t nodos_visitados = 1;

    while (nodos_visitados < matriz_adyacencia.columnas()) {
        int arista_mayor_peso = -1;
        size_t nodo_inicio = 0;
        size_t nodo_final = 0;
        bool arista_encontrada = false;

        for (size_t i = 0; i < matriz_adyacencia.filas(); i++) {
            if (vertices_visitados[i]) {
                for (size_t j = 0; j < matriz_adyacencia.columnas(); j++) {
                    if (!vertices_visitados[j] && matriz_adyacencia.elemento(i, j) > arista_mayor_peso && matriz_adyacencia.elemento(i, j) != INFINITO) {
                        arista_mayor_peso = matriz_adyacencia.elemento(i, j);
                        nodo_inicio = i;
                        nodo_final = j;
                        arista_encontrada = true;
                    }
                }
            }
        }

        if (arista_encontrada) {
            aristas_maximas.push_back({{nodo_inicio, nodo_final}, arista_mayor_peso});
            vertices_visitados[nodo_final] = true;
            nodos_visitados++;
        } else {
            nodos_visitados = matriz_adyacencia.columnas();
        }
    }

    return aristas_maximas;
}