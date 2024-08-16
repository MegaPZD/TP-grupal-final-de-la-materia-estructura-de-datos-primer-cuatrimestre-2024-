#include "arista.hpp"

arista::arista(std::pair<size_t, size_t> vertices, int peso) {
    this->vertices = vertices;
    this->peso = peso;
}

arista::arista() : arista({0, 0}, 0) {}

std::pair<size_t, size_t> arista::obtener_vertices() {
    return vertices;
}

int arista::obtener_peso() {
    return peso;
}

bool arista::operator==(std::pair<size_t, size_t> vertices1) {
    return (vertices.first == vertices1.first && vertices.second == vertices1.second) ||
           (vertices.first == vertices1.second && vertices.second == vertices1.first);
}