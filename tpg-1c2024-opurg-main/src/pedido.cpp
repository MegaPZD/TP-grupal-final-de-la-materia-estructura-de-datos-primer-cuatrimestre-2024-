#include "pedido.hpp"

pedido::pedido(coordenada inicio, coordenada final, size_t peso, size_t prio_local)
    : inicio(inicio), final(final), peso(peso), prioridad(prio_local*peso) {
}

coordenada pedido::obtener_origen(){
    return inicio;
}

coordenada pedido::obtener_destino(){
    return final;
}

size_t pedido::obtener_prioridad(){
    return prioridad;
}

pedido::~pedido() {

}