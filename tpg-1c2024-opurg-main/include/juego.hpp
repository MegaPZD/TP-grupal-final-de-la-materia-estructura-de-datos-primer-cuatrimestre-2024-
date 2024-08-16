#ifndef AYED_TPG_1C2024_JUEGO_HPP
#define AYED_TPG_1C2024_JUEGO_HPP

#include <functional>

// Minijuego 1
#include "mapa.hpp"
#include "matriz.hpp"
#include "colores.hpp"
#include "a_estrella.hpp"
#include "coordenada.hpp"

#include "local.hpp"
#include "diccionario.hpp"
#include "pedido.hpp"

// Minijuego 2
#include "grafo.hpp"

const int MIN_PESO_PEDIDO = 1;
const int MAX_PESO_PEDIDO = 4;
const int MIN_CANT_PEDIDO = 2;
const int MAX_CANT_PEDIDO = 6;

bool comp_nombre(std::string local1, std::string local2);

class juego {
private:
    // Juego 1
    mapa mapa1;
    diccionario< std::string , local , comp_nombre>  locales;
    a_estrella minijuego1;

    // Juego 2
    grafo minijuego2;

    // Pre: exclude debe ser: 1 <= exclude <= cantidad_locales.
    // Post: Devuelve un numero entre 1 y la cantidad de locales excluyendo
    // exclude.
    int generar_numero_random_excluyente(int exclude);

    // Pre: La ubicación y cantidad de los locales deben ser correctamente inicializadas.
    // Post: Crea cant_locales locales.
    local crear_local(std::vector<coordenada> ubicacion_locales, size_t cant_locales);

    // Pre: Deben existir por lo menos 2 locales, origen y destino.
    // Post: Devuelve un pedido de origen a destino.
    // A su vez con el pedido también se inicializan las aristas de minijuego2.
    void asignar_pedidos_arista(local* origen, local destino);

    // Pre: Deben existir por lo menos 2 locales, origen y destino
    // Post: Crea una cantidad_pedidos, y las agrega al heap_pedidos del local origen.
    void listado_pedidos(local* origen);

    // Pre: Debe haber un class mapa creado.
    // Post: Actualiza el mapa posterior a la creación de un camino.
    // Esto implica mover los clientes, mostrarlos nuevamente y mostrar por pantalla
    // el camino generado.
    void actualizar_mapa_con_camino_actual(std::stack<coordenada> camino, coordenada origen, coordenada destino);

    // Pre: -
    // Post: Imprimir juego en terminal
    void imprimir_mapa();

    // Pre: -
    // Post: Reinicia el mapa. Esto implica actualizar las casillas CAMINADO y CLIENTE
    // por CAMINABLE y reiniciar el vector de clientes volviéndolo a generar y
    // poner sus coordenadas en el mapa.
    void reiniciar_mapa();

    //Modularización de resolver, es la función que se ejecutará en el diccionario
    //de locales.
    // Pre: Se requiere que los locales estén correctamente inicializados
    // Post: Ejecuta los minijuegos: esto implica resolver todos los pedidos
    // de todos los locales, imprimir ambos minijuegos y refrescar el mapa.
    void resolver_minijuegos(local local1);

public:
    //Constructor
    juego();

    // Pre: Se requiere que los locales estén correctamente inicializados
    // Post: Ejecuta los minijuegos: esto implica resolver todos los pedidos
    // de todos los locales, imprimir ambos minijuegos y refrescar el mapa.
    void resolver();
    
    template<typename c, typename T, bool comp(c, c)>
    friend class diccionario;
};

#endif //AYED_TPG_1C2024_JUEGO_HPP
