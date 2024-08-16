#ifndef MATRIZ_H
#define MATRIZ_H

#include <exception>
#include <cstddef>
#include <utility>

class indice_no_valido_exception : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Error: el indice ingresado no es valido.";
    }
};

class dimensiones_no_validas_exception : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Error: las dimensiones no son validas.";
    }
};

template<typename T>
class matriz {
protected:
    T* datos;
    size_t f;
    size_t c;

    // Pre: -
    // Post: Devuelve true si el indice es valido (0 <= i < filas, 0 <= j < columnas).
    bool indice_valido(size_t i, size_t j);

    // Pre: El índice bidimensional debe ser valido.
    // Post: Devuelve el indice unidimensional equivalente al ingresado.
    size_t calcular_indice(size_t i, size_t j);

public:
    // Constructor default.
    // NOTA: No tiene sentido una matríz 0x0, por lo que no se debería usar directamente.
    // Está implementado solamente por temas de C++ (default-constructible).
    matriz();

    // Pre: Tamaño no puede ser menor que 1.
    // Post: Genera una matriz cuadrada con el tamaño indicado, inicializada con el valor ingresado.
    matriz(size_t tamanio, T valor);

    // Pre: Tamaño no puede ser menor que 1.
    // Post: Genera una matriz cuadrada vacía con el tamaño indicado.
    matriz(size_t tamanio);

    // Pre: Ninguna de las dimensiones puede ser menor que 1.
    // Post: Genera una matriz con las dimensiones indicadas, inicializada con el valor ingresado.
    matriz(size_t filas, size_t columnas, T valor);

    // Pre: Ninguna de las dimensiones puede ser menor que 1.
    // Post: Genera una matriz vacía con las dimensiones indicadas.
    matriz(size_t fila, size_t columna);

    // Constructor de copia.
    matriz(const matriz& matriz1);

    // Operador de asignación.
    matriz& operator=(const matriz& matriz1);

    // Pre: El índice debe ser válido, es decir, 0 <= i < filas, 0 <= j < columnas.
    // Post: Devuelve una referencia al elemento accedido.
    T& elemento(size_t i, size_t j);

    // Pre: Ninguna de las dimensiones puede ser menor que 1.
    // Post: Redimensiona la matriz al tamaño deseado. Los datos anteriores son copiados, de ser posible.
    void redimensionar(size_t filas, size_t columnas);

    // Pre: -
    // Post: Devuelve la cantidad de filas de la matriz.
    size_t filas();

    // Pre: -
    // Post: Devuelve la cantidad de columnas de la matriz.
    size_t columnas();

    //Pre: indice debe ser valido.
    //Post: Cambia el valor del elemento en la fila y columnaindicada dentro de la matriz.
    void modificar_elemento(size_t fila, size_t columna, T valor);

    // Destructor.
    ~matriz();
};

template<typename T>
matriz<T>::matriz() {
    f = 0;
    c = 0;
    datos = nullptr;
}

template<typename T>
matriz<T>::matriz(size_t filas, size_t columnas, T valor) {
    if (filas < 1 || columnas < 1) {
        throw dimensiones_no_validas_exception();
    }
    f = filas;
    c = columnas;
    datos = new T[f * c];
    for (size_t i = 0; i < f * c; i++) {
        datos[i] = valor;
    }
}

template<typename T>
matriz<T>::matriz(size_t fila, size_t columna) : matriz(fila, columna, T()) {}

template<typename T>
matriz<T>::matriz(size_t tamanio, T valor) : matriz(tamanio, tamanio, valor) {}

template<typename T>
matriz<T>::matriz(size_t tamanio) : matriz(tamanio, tamanio, T()) {}

template<typename T>
matriz<T>::matriz(const matriz& matriz1) {
    f = matriz1.f;
    c = matriz1.c;
    datos = nullptr;
    if (matriz1.datos) {
        datos = new T[f * c];
        for (size_t i = 0; i < f * c; i++) {
            datos[i] = matriz1.datos[i];
        }
    }
}

template<typename T>
matriz<T>& matriz<T>::operator=(const matriz& matriz1) {
    if (this != &matriz1) {
        delete[] datos;
        f = matriz1.f;
        c = matriz1.c;
        datos = nullptr;
        if (matriz1.datos) {
            datos = new T[f * c];
            for (size_t i = 0; i < f * c; i++) {
                datos[i] = matriz1.datos[i];
            }
        }
    }
    return *this;
}

template<typename T>
bool matriz<T>::indice_valido(size_t i, size_t j) {
    return i < f && j < c;
}

template<typename T>
size_t matriz<T>::calcular_indice(size_t i, size_t j) {
    return i * c + j;
}

template<typename T>
T& matriz<T>::elemento(size_t i, size_t j) {
    if (!(i < f && j < c)) {
        throw indice_no_valido_exception();
    }
    return datos[calcular_indice(i, j)];
}

template<typename T>
void matriz<T>::redimensionar(size_t filas, size_t columnas) {
    if (filas < 1 || columnas < 1) {
        throw dimensiones_no_validas_exception();
    }
    T* aux = new T[filas * columnas];
    for (size_t i = 0; i < filas; i++) {
        for (size_t j = 0; j < columnas; j++) {
            try {
                aux[i * columnas + j] = elemento(i, j);
            } catch (indice_no_valido_exception& e) {
                aux[i * columnas + j] = T();
            }
        }
    }
    f = filas;
    c = columnas;
    delete[] datos;
    datos = aux;
}

template<typename T>
size_t matriz<T>::filas() {
    return f;
}

template<typename T>
size_t matriz<T>::columnas() {
    return c;
}

template<typename T>
void matriz<T>::modificar_elemento(size_t fila, size_t columna, T valor){
    if (!(fila < f && columna < c)) {
        throw indice_no_valido_exception();
    }
    datos[calcular_indice(fila, columna)] = valor;
}

template<typename T>
matriz<T>::~matriz() {
    delete[] datos;
}

#endif