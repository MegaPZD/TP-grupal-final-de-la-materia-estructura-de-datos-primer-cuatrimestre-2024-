#ifndef AYED_TPG_1C2024_MAPA_HPP
#define AYED_TPG_1C2024_MAPA_HPP

#include "coordenada.hpp"
#include "matriz.hpp"
#include <iostream>
#include <vector>

const int FILAS = 18;
const int COLUMNAS = 24;
const int MAX_LOCALES = 6;
const int MIN_LOCALES = 4;
const int MAX_CLIENTES = 4;
const int MIN_CLIENTES = 0;

/* Esta clase es la encargada de decirle a a_estrella si la posición de un vecino es válida o no.
 * Queda a criterio del grupo como implementarla. La idea es que a_estrella no tenga detalles de
 * implementación de posibles casilleros, clientes, paredes, locales, etc.
 * Adicionalmente, la pueden utilizar para otras partes del TP.
 * TIP: Tienen una matriz ya implementada como parte de la plantilla del TP. */

enum tipo_casilla {
    PARED = 0,
    CAMINABLE = 1,
    LOCAL = 2,
    CLIENTE = 3,
    CAMINADO = 4
};

class mapa {
private:
    std::vector<std::pair<size_t, size_t>> casilleros_caminables;
    matriz<tipo_casilla> mapa_completo;
    std::vector<coordenada> posiciones_clientes;
    std::vector<coordenada> posiciones_locales;


    //Pre: -
    //Post: Genera una coordenada valida y caminable que es parte de la matriz.
    coordenada generar_coordenadas_aleatoria();

    // Pre: -
    // Post: Genera un vector con las ubicaciones de los clientes que serán obstáculos.
    std::vector<coordenada> coordenadas_locales();

    // Pre: -
    // Post: Genera un vector con las ubicaciones de los clientes que serán obstáculos.
    std::vector<coordenada> coordenadas_clientes();

public:
    //Constructor
    mapa();

    // Pre: -
    // Post: Devuelve true si la posición del vecino es válida (es decir, es una coordenada válida y es caminable).
    bool es_vecino_valido(coordenada posicion);

    // Pre: -
    // Post: Devuelve un vector con las coordenadas válidas de los vecinos de la posición dada.
    std::vector<coordenada> obtener_vecinos_validos(coordenada pos_actual, coordenada destino);

    // Pre: -
    // Post: Deja el vector posiciones_clientes sin elementos y vuelve a generar
    // clientes en el tablero. 
    void mover_clientes();



    // Pre: -
    // Post: Devuelve el atributo posiciones_locales, que es un vector de coordenadas.
    std::vector<coordenada> obtener_posiciones_locales();

    // Pre: -
    // Post: Devuelve el valor enum tipo_casilla de la coordenada pasada como argumento.
    tipo_casilla obtener_casilla(coordenada posicion);

    // Pre: -
    // Post: Devuelve la cantidad de locales
    size_t obtener_cant_locales();

    //Pre: indice debe ser valido.
    //Post: Ejecuta modificar_elemento en mapa_completo.
    void modificar_elemento_en_mapa(size_t fila, size_t columna, tipo_casilla tipo);
};

#endif