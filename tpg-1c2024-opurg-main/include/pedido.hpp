#ifndef AYED_TPG_1C2024_PEDIDO_HPP
#define AYED_TPG_1C2024_PEDIDO_HPP

#include <cstddef>
#include "coordenada.hpp"

class pedido {
private:
    coordenada inicio;
    coordenada final;
    size_t peso;
    size_t prioridad;

public:
    // Constructor
    pedido(coordenada inicio, coordenada final, size_t peso, size_t prio_local);

    // Pre: -
    // Post: Devuelve las coordenadas del local de origen
    coordenada obtener_origen();

    // Pre: -
    // Post: Devuelve el local de destino
    coordenada obtener_destino();

    // Pre: -
    // Post: Devuelve la prioridad del pedido
    size_t obtener_prioridad();

    // Destructor
    ~pedido();
};


#endif //AYED_TPG_1C2024_PEDIDO_HPP
