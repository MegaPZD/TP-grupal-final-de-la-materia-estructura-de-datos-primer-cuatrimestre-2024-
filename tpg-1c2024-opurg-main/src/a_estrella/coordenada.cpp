#include "coordenada.hpp"

coordenada::coordenada(int x, int y) : std::pair<int, int>(x, y) {}

coordenada::coordenada() : coordenada(0, 0) {}

coordenada coordenada::operator-(coordenada coordenada1) {
    return {x() - coordenada1.x(), y() - coordenada1.y()};
}

int coordenada::x() {
    return first;
}

int coordenada::y() {
    return second;
}