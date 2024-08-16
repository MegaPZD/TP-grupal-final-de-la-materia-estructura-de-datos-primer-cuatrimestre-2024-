#include "vertice.hpp"

vertice::vertice(coordenada posicion, vertice* padre) {
    this->posicion = posicion;
    this->padre = padre;
    costo_origen = 0;
    distancia_destino = 0;
}

vertice::vertice(coordenada posicion) : vertice(posicion, nullptr) {}

vertice::vertice() : vertice({0, 0}, nullptr) {}

bool vertice::operator<(const vertice& vertice1) {
    return distancia_destino < vertice1.distancia_destino;
}

bool vertice::operator==(const vertice& vertice1) const {
    return posicion == vertice1.posicion;
}

bool vertice::operator==(const coordenada& posicion1) const {
    return posicion == posicion1;
}

coordenada vertice::operator-(const vertice& vertice1) {
    return posicion - vertice1.posicion;
}

bool vertice::menor(vertice* vertice1, vertice* vertice2) {
    return *vertice1 < *vertice2;
}

bool vertice::igual(vertice* vertice1, vertice* vertice2) {
    return *vertice1 == *vertice2;
}