#ifndef AYED_TPG_1C2024_ARISTA_HPP
#define AYED_TPG_1C2024_ARISTA_HPP

#include <cstddef>
#include <utility>

/* Esta clase es utilitaria:
 * Los vértices están guardados en un std::pair, para que luego puedan asociarlos a los locales.
 * Se incluye el peso para probar el correcto funcionamiento de obtener_aem().
 * Se considera que esta arista es no direccionada.
 * Para más información, ver este enlace: https://en.cppreference.com/w/cpp/utility/pair */

class arista {
private:
    std::pair<size_t, size_t> vertices;
    int peso;
public:
    // Constructores.
    arista();

    arista(std::pair<size_t, size_t> vertices, int peso);

    // Pre: -
    // Post: Devuelve los vértices asociados a la arista.
    std::pair<size_t, size_t> obtener_vertices();

    // Pre: -
    // Post: Devuelve el peso de la arista.
    int obtener_peso();

    // Pre: -
    // Post: Devuelve true si los vertices coinciden (independientemente del orden).
    // Por ejemplo, {1, 3} es la misma arista que {3, 1}.
    // NOTA: Este operador está principalmente para probar obtener_aem().
    bool operator==(std::pair<size_t, size_t> vertices1);
};

#endif