#ifndef AYED_TPG_1C2024_NODO_HPP
#define AYED_TPG_1C2024_NODO_HPP

template<typename c, typename T, bool comp(c, c)>
class diccionario;

template<typename c, typename T, bool comp(c, c)>
class nodo {
private:
    c clave{};
    T dato{};
    nodo<c, T, comp>* padre;
    nodo<c, T, comp>* hijo_izquierdo;
    nodo<c, T, comp>* hijo_derecho;

    // Constructores.
    nodo(c clave, T dato);

    nodo(c clave, T dato, nodo<c, T, comp>* padre, nodo<c, T, comp>* hijo_izquierdo, nodo<c, T, comp>* hijo_derecho);

    // Esto permite acceder directamente a los atributos del nodo.
    friend class diccionario<c, T, comp>;
};

template<typename c, typename T, bool comp(c, c)>
nodo<c, T, comp>::nodo(c clave, T dato) {
    this->clave = clave;
    this->dato = dato;
    padre = nullptr;
    hijo_izquierdo = nullptr;
    hijo_derecho = nullptr;
}

template<typename c, typename T, bool (* comp)(c, c)>
nodo<c, T, comp>::nodo(c clave, T dato, nodo<c, T, comp>* padre, nodo<c, T, comp>* hijo_izquierdo,
                       nodo<c, T, comp>* hijo_derecho) {
    this->clave = clave;
    this->dato = dato;
    this->padre = padre;
    this->hijo_izquierdo = hijo_izquierdo;
    this->hijo_derecho = hijo_derecho;
}

#endif