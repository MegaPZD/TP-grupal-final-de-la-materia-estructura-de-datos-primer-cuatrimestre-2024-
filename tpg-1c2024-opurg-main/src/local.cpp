#include "local.hpp"

bool comp_prioridad(pedido p1, pedido p2) {
    return p1.obtener_prioridad() > p2.obtener_prioridad();
}

local::local(): nombre_local(""), ubicacion(coordenada(-1,-1)), prioridad(0) {
};

local::local(std::string nombre_local, coordenada ubicacion, size_t prioridad)
        : nombre_local(nombre_local), ubicacion(ubicacion), prioridad(prioridad){
}

void local::crear_pedido(local& origen, local& destino, size_t peso, size_t prio_local) {
    pedido nuevo_pedido(coordenada(origen.obtener_pos_X(), origen.obtener_pos_Y()),
                        coordenada(destino.obtener_pos_X(), destino.obtener_pos_Y()),
                        peso, prio_local);

    heap_pedidos.alta(nuevo_pedido);
}

pedido local::obtener_pedido_prioritario() {
    return heap_pedidos.primero();
}

int local::obtener_pos_X() {
    return ubicacion.x();
}

int local::obtener_pos_Y() {
    return ubicacion.y();
}

std::string local::obtener_nombre() {
    return nombre_local;
}

size_t local::prioridad_local(){
    return prioridad;
}

void local::eliminar_pedido_prioritario(){
    heap_pedidos.baja();
}

size_t local::tamanio_del_heap_actual(){
    return heap_pedidos.tamanio();
}

local::~local() {
}



