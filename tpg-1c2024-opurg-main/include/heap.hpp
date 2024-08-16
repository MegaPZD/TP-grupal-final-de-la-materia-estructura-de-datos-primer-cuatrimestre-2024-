#ifndef AYED_TPG_1C2024_HEAP_HPP
#define AYED_TPG_1C2024_HEAP_HPP

#include <vector>
#include <cstdlib>
#include <exception>

class heap_exception : public std::exception {
};

template<typename T, bool comp(T, T)>
class heap {
private:
    std::vector<T> datos;

    // Pre: Ambos índices deben ser menor que la cantidad de datos.
    // Post: Intercambia de lugar los datos de los indices indicados.
    void swap(size_t indice_1, size_t indice_2);

    // Pre: Ambos índices deben ser menor que la cantidad de datos.
    // Post: Realiza un "upheap" sobre los índices indicados.
    // (El dato "sube" en el heap.)
    void upheap(size_t& indice, size_t&contador);

    // Post: El índice debe ser menor que la cantidad de datos.
    // Post: Realiza un "downheap" sobre el índice indicado.
    // (El dato "baja" en el heap, intercambiándose con el menor/mayor dato.)
    void downheap(size_t& indice, size_t&contador);

    // NOTA: No es necesario que lancen excepciones en estos métodos porque son privados.
    // Deberían siempre asegurar que los índices pasados por parámetros son válidos.
    // Consideren cada caso con detenimiento.
    // Adicionalmente, tengan cuidado con el casteo de las variables, porque son size_t.
    // Hacer, por ejemplo, size_t i = 0; i - 1; produce un underflow.
public:
    // Constructor.
    heap();

    // Pre: -
    // Post: Agrega el dato al heap.
    void alta(T dato);

    // Pre: El heap no puede estar vacío.
    // Post: Elimina y devuelve el primer dato.
    T baja();

    // Método para el informe de complejidad algorítmica. Devuelve la cantidad de "upheaps".
    size_t alta_complejidad(T dato);

    // Método para el informe de complejidad algorítmica. Devuelve la cantidad de "downheaps".
    size_t baja_complejidad();

    // Pre: El heap no puede estar vacío.
    // Post: Devuelve el primer dato.
    T primero();

    // Pre: -
    // Post: Devuelve true si el heap está vacío.
    bool vacio();

    // Pre: -
    // Post: Devuelve la cantidad de datos en el heap.
    size_t tamanio();

    // Destructor.
    ~heap();
};

template<typename T, bool (* comp)(T, T)>
heap<T, comp>::heap() {

}

template<typename T, bool (* comp)(T, T)>
void heap<T, comp>::swap(size_t indice_1, size_t indice_2) {
    T auxiliar = datos[indice_1];
    datos[indice_1] = datos[indice_2];
    datos[indice_2] = auxiliar;
}

template<typename T, bool (* comp)(T, T)>
void heap<T, comp>::upheap(size_t& indice, size_t& contador) {
    size_t padre = (indice - 1) / 2;
    while (indice > 0 && comp(datos[indice], datos[padre])) {
        swap(indice, padre);
        indice = padre;
        padre = (indice - 1) / 2;
        contador++;
    }
}


template<typename T, bool (* comp)(T, T)>
void heap<T, comp>::downheap(size_t& indice, size_t& contador) {
    size_t size = datos.size();

    size_t indice_hijo_izquierdo = 2 * indice + 1;
    size_t indice_hijo_derecho = 2 * indice + 2;
    size_t ha_bajar = indice;

    bool en_posicion = false;
    while(!en_posicion){

        indice_hijo_izquierdo = 2 * indice + 1;
        indice_hijo_derecho = 2 * indice + 2;
        ha_bajar = indice;

        if (indice_hijo_izquierdo < size && comp(datos[indice_hijo_izquierdo], datos[ha_bajar])){
            ha_bajar = indice_hijo_izquierdo;
        }

        if (indice_hijo_derecho < size && comp(datos[indice_hijo_derecho], datos[ha_bajar])){
            ha_bajar = indice_hijo_derecho;
        }

        if (ha_bajar == indice){
            en_posicion = true;
        }

        swap(indice, ha_bajar);
        indice = ha_bajar;
        contador++;
    }
}

template<typename T, bool (* comp)(T, T)>
void heap<T, comp>::alta(T dato) {
    datos.push_back(dato);
    size_t indice = datos.size() - 1;
    size_t contador = 0;
    upheap(indice, contador);
}

template<typename T, bool (* comp)(T, T)>
T heap<T, comp>::baja() {
    if(vacio()){
        throw heap_exception();
    }
    T dato_eliminado = datos[0];
    datos[0] = datos.back();
    datos.pop_back();

    if(vacio()){
        throw heap_exception();
    }

    size_t cero = 0;
    size_t contador = 0;
    downheap(cero, contador);

    return dato_eliminado;
}


template<typename T, bool (* comp)(T, T)>
size_t heap<T, comp>::alta_complejidad(T dato) {
    datos.push_back(dato);
    size_t indice = datos.size() - 1;
    size_t contador = 0;
    upheap(indice, contador);
    return contador;
}

template<typename T, bool (* comp)(T, T)>
size_t heap<T, comp>::baja_complejidad() {
    if (vacio()) {
        throw heap_exception();
    }

    datos[0] = datos.back();
    datos.pop_back();

    if (vacio()) {
        return 0;
    }

    size_t cero = 0;
    size_t contador = 0;
    downheap(cero, contador);

    return contador;
}

template<typename T, bool (* comp)(T, T)>
T heap<T, comp>::primero() {
    if(vacio()){
        throw heap_exception();
    }
    return datos[0];
}

template<typename T, bool (* comp)(T, T)>
bool heap<T, comp>::vacio() {
    return datos.empty();
}

template<typename T, bool (* comp)(T, T)>
size_t heap<T, comp>::tamanio() {
    return datos.size();
}

template<typename T, bool (* comp)(T, T)>
heap<T, comp>::~heap() {
    datos.clear();
}

#endif
