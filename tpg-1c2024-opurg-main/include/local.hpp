#ifndef AYED_TPG_1C2024_LOCAL_HPP
#define AYED_TPG_1C2024_LOCAL_HPP

#include "coordenada.hpp"
#include "heap.hpp"
#include "pedido.hpp"
#include <iostream>

bool comp_prioridad(pedido p1, pedido p2);

class local{
private:
    std::string nombre_local;
    coordenada ubicacion;
    size_t prioridad;
    // Lista de pedidos
    heap<pedido, comp_prioridad> heap_pedidos{};

public:
    //Constructores
    local();
    local(std::string nombre_local, coordenada ubicacion, size_t prioridad);

    // Pre: Un local_origen y su local_destino
    // Post: Crea un pedido y lo agrega a heap_pedidos
    void crear_pedido(local& origen, local& destino, size_t peso, size_t prio_local);

    // Pre: -
    // Post: Devuelve la posición en X en la cuadrilla (en coordenadas)
    int obtener_pos_X();

    // Pre: -
    // Post: Devuelve la posición en Y en la cuadrilla (en coordenadas)
    int obtener_pos_Y();

    // Pre: -
    // Post: Devuelve el pedido con mayor prioridad
    pedido obtener_pedido_prioritario();

    // Pre: -
    // Post: Devuelve el nombre del local
    std::string obtener_nombre();

    // Pre: -
    // Post: Devuelve la prioridad del local
    size_t prioridad_local();

    // Pre: -
    // Post: Elimina el pedido_prioritario
    void eliminar_pedido_prioritario();

    // Pre: -
    // Post: Devuelve el tamanio de heap
    size_t tamanio_del_heap_actual();

    // Destructor
    ~local();
};

#endif //AYED_TPG_1C2024_LOCAL_HPP
