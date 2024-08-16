#ifndef AYED_TPG_1C2024_DICCIONARIO_HPP
#define AYED_TPG_1C2024_DICCIONARIO_HPP

#include <exception>
#include <cstdlib>
#include <vector>
#include <queue>
#include <functional>
#include "nodo.hpp"

using namespace std;

class diccionario_exception : public std::exception {
};

template<typename c, typename T, bool comp(c, c)>
class diccionario {
private:
    // comp es la función de comparación para las claves.
    // La clave debe implementar el operator==().
    nodo<c, T, comp>* raiz;
    std::size_t cantidad_datos;

    // Pre: -
    // Post: Devuelve el recorrido inorder recursivamente.
    void inorder_recursivo(nodo<c, T, comp>* padre1, vector<T>* vector);

    // Pre: -
    // Post: Devuelve el recorrido preorder recursivamente.
    void preorder_recursivo(nodo<c, T, comp>* padre1, vector<T>* vector);

    // Pre: -
    // Post: Devuelve el recorrido postorder recursivamente.
    void postorder_recursivo(nodo<c, T, comp>* padre1, vector<T>* vector);

    // Pre: -
    // Post: Devuelve el recorrido borra ABB recursivamente.
    void borrar_ABB_recursivo(nodo<c, T, comp>* padre1);

    // Pre: -
    // Post: Ejecuta el método/función en cada valor del árbol recursivamente.
    void ejecutar_recursivo(nodo<c, T, comp>* nodo_actual, std::function<void(T)> funcion);

    nodo<c,T, comp>* buscar_nodo(c clave, nodo<c, T, comp>* actual);

    // Distintos casos de baja
    void eliminar_nodo_hoja(nodo<c, T, comp>* nodo_a_eliminar);
    void eliminar_nodo_un_hijo(nodo<c,T, comp>* nodo_a_eliminar);
    void eliminar_nodo_dos_hijos(nodo<c, T, comp>* nodo_a_eliminar);
public:
    // Constructor.
    diccionario();

    // Pre: La clave no puede existir en el árbol.
    // Post: Agrega el dato asociado a la clave al árbol. Si no hay datos, crea una nueva raíz.
    void alta(c clave, T dato);

    // Pre: -
    // Post: Elimina el dato asociado a la clave del árbol. Si no existe, no hace nada.
    // NOTA: El caso de baja con dos hijos se resuelve con sucesor inmediato. Se puede hacer swap del dato.
    void baja(c clave);

    // Pre: La clave debe existir en el árbol.
    // Post: Devuelve una referencia al valor asociado a la clave.
    T& operator[](c clave);

    // Pre: -
    // Post: Devuelve el recorrido inorder.
    std::vector<T> inorder();

    // Pre: -
    // Post: Devuelve el recorrido preorder.
    std::vector<T> preorder();

    // Pre: -
    // Post: Devuelve el recorrido postorder.
    std::vector<T> postorder();

    // Pre: -
    // Post: Devuelve el recorrido en ancho.
    std::vector<T> ancho();

    // Pre: -
    // Post: Ejecuta el método/función en cada valor del árbol.
    /* NOTA: No abusar de este método, está solamente para simplificar algunas cosas,
     * como liberar la memoria de los nodos de usar punteros o imprimir por pantalla el contenido.
     * Pueden usar cualquier recorrido. */
    void ejecutar(std::function<void(T)> funcion);

    // Pre: -
    // Post: Devuelve la cantidad de datos en el árbol.
    std::size_t tamanio();

    // Pre: -
    // Post: Devuelve true si el árbol está vacío.
    bool vacio();

    // El constructor de copia está deshabilitado.
    diccionario(const diccionario& abb) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const diccionario& abb) = delete;

    // Destructor.
    ~diccionario();
};

template<typename c, typename T, bool (* comp)(c, c)>
diccionario<c, T, comp>::diccionario() {
    raiz = nullptr;
    cantidad_datos = 0;
}

template<typename c, typename T, bool (* comp)(c, c)>
void diccionario<c, T, comp>::alta(c clave, T dato) {
    if (buscar_nodo(clave, raiz) != nullptr){
        throw diccionario_exception();
    }
    nodo<c, T, comp>* nuevo_nodo = new nodo<c, T, comp>(clave, dato);

    if( raiz == nullptr ){
        raiz = nuevo_nodo;
    }
    else{
        nodo<c, T, comp>* actual = raiz;
        nodo<c, T, comp>* padre = nullptr;

        // Recorro el árbol, para encontrar el lugar de nuevo_nodo
        while( actual != nullptr){
            padre = actual;

            if( comp(clave, actual->clave) ){
                actual = actual->hijo_izquierdo;
            }
            else{
                actual = actual->hijo_derecho;
            }
        }
        nuevo_nodo->padre = padre;

        if( comp(clave, padre->clave) ){
            padre->hijo_izquierdo = nuevo_nodo;
        }
        else{
            padre->hijo_derecho = nuevo_nodo;
        }
    }
    cantidad_datos++;
}

template<typename c, typename T, bool (*comp)(c, c)>
nodo<c, T, comp> *diccionario<c, T, comp>::buscar_nodo(c clave, nodo<c, T, comp>* actual) {
    if(actual == nullptr){
        return nullptr;
    }
    if( clave == actual->clave ){
        return actual;
    }
    if(comp(clave, actual->clave)){
        return buscar_nodo(clave, actual->hijo_izquierdo);
    } else{
        return buscar_nodo(clave, actual->hijo_derecho);
    }

}

template<typename c, typename T, bool (*comp)(c, c)>
void diccionario<c, T, comp>::eliminar_nodo_hoja(nodo<c, T, comp>* nodo_a_eliminar) {
    if (nodo_a_eliminar == raiz) {
        raiz = nullptr;
    } else {
        nodo<c, T, comp>* padre = nodo_a_eliminar->padre;
        if (padre->hijo_izquierdo == nodo_a_eliminar) {
            padre->hijo_izquierdo = nullptr;
        } else if (padre->hijo_derecho == nodo_a_eliminar){
            padre->hijo_derecho = nullptr;
        }
    }
    delete nodo_a_eliminar;
}


template<typename c, typename T, bool (*comp)(c, c)>
void diccionario<c, T, comp>::eliminar_nodo_un_hijo(nodo<c, T, comp>* nodo_a_eliminar) {
    nodo<c, T, comp>* hijo = (nodo_a_eliminar->hijo_izquierdo != nullptr) ? nodo_a_eliminar->hijo_izquierdo : nodo_a_eliminar->hijo_derecho;

    nodo_a_eliminar->clave = hijo->clave;
    nodo_a_eliminar->dato = hijo->dato;
    eliminar_nodo_hoja(hijo);
}

template<typename c, typename T, bool (*comp)(c, c)>
void diccionario<c, T, comp>::eliminar_nodo_dos_hijos(nodo<c, T, comp>* nodo_a_eliminar) {
    nodo<c, T, comp>* sucesor = nodo_a_eliminar->hijo_derecho;
    while (sucesor->hijo_izquierdo != nullptr) {
        sucesor = sucesor->hijo_izquierdo;
    }

    nodo_a_eliminar->clave = sucesor->clave;
    nodo_a_eliminar->dato = sucesor->dato;

    if (sucesor->hijo_izquierdo != nullptr) {
        eliminar_nodo_un_hijo(sucesor);
    } else {
        eliminar_nodo_hoja(sucesor);
    }
}

template<typename c, typename T, bool (* comp)(c, c)>
void diccionario<c, T, comp>::baja(c clave) {

    nodo<c, T, comp>* nodo_a_eliminar = buscar_nodo(clave, raiz);
    if (nodo_a_eliminar != nullptr) {
        // Case 1: El nodo a eliminar no tiene hijos
        if (nodo_a_eliminar->hijo_izquierdo == nullptr && nodo_a_eliminar->hijo_derecho == nullptr) {
            eliminar_nodo_hoja(nodo_a_eliminar);
        }
        // Case 2: El nodo a eliminar tiene un solo hijo
        else if (nodo_a_eliminar->hijo_izquierdo == nullptr || nodo_a_eliminar->hijo_derecho == nullptr) {
            eliminar_nodo_un_hijo(nodo_a_eliminar);
        }
        // Case 3: El nodo a eliminar tiene 2 hijos
        else {
            eliminar_nodo_dos_hijos(nodo_a_eliminar);
        }
        cantidad_datos--;
    }
}

template<typename c, typename T, bool (* comp)(c, c)>
T& diccionario<c, T, comp>::operator[](c clave) {
    nodo<c, T, comp>* nodo_objetivo = buscar_nodo(clave, raiz);
    if( nodo_objetivo == nullptr ){
        throw diccionario_exception();
    }
    return  nodo_objetivo->dato;
}

// Su recursividad es multiple, directa y de cola.
template<typename c, typename T, bool (* comp)(c, c)>
void diccionario<c, T, comp>::inorder_recursivo(nodo<c, T, comp>* padre1, vector<T>* vector){
    if (padre1 != nullptr)
    {
        inorder_recursivo(padre1->hijo_izquierdo, vector);
        vector->push_back(padre1->dato);
        inorder_recursivo(padre1->hijo_derecho, vector);
    }
}

//Esta función recorre la función de la siguient manera: Izquierdo, Raíz, Derecho. Su recursividad es simple, directa y de cola.
template<typename c, typename T, bool (* comp)(c, c)>
std::vector<T> diccionario<c, T, comp>::inorder() {
    std::vector<T> recorrido;
    inorder_recursivo(raiz, &recorrido);
    return recorrido; // es nullptr si el ABB esta vacio
}

// Su recursividad es multiple, directa y de cola.
template<typename c, typename T, bool (* comp)(c, c)>
void diccionario<c, T, comp>::preorder_recursivo(nodo<c, T, comp>* padre1, vector<T>* vector){
    if (padre1 != nullptr){
        vector->push_back(padre1->dato);
        preorder_recursivo(padre1->hijo_izquierdo, vector);
        preorder_recursivo(padre1->hijo_derecho, vector);
    }
}

//Esta función recorre la función de la siguient manera: Raíz, Izquierda, Derecho. Su recursividad es simple, directa y de cola.
template<typename c, typename T, bool (* comp)(c, c)>
std::vector<T> diccionario<c, T, comp>::preorder() {
    std::vector<T> recorrido;
    preorder_recursivo(raiz, &recorrido);
    return recorrido; // es nullptr si el ABB esta vacio
}

//Su recursividad es multiple, directa y de cola.
template<typename c, typename T, bool (* comp)(c, c)>
void diccionario<c, T, comp>::postorder_recursivo(nodo<c, T, comp>* padre1, vector<T>* vector){
    if (padre1 != nullptr){
        postorder_recursivo(padre1->hijo_izquierdo, vector);
        postorder_recursivo(padre1->hijo_derecho, vector);
        vector->push_back(padre1->dato);
    }
}

//Esta función recorre la función de la siguient manera: Izquierda, Derecho, Raíz. Su recursividad es simple, directa y de cola.
template<typename c, typename T, bool (* comp)(c, c)>
std::vector<T> diccionario<c, T, comp>::postorder() {
    std::vector<T> recorrido;
    postorder_recursivo(raiz, &recorrido);
    return recorrido; // es nullptr si el ABB esta vacio
}

template<typename c, typename T, bool (* comp)(c, c)>
std::vector<T> diccionario<c, T, comp>::ancho() {

    queue<nodo<c, T, comp>> cola;

    vector<T> resultado;

    if (raiz != nullptr){
        cola.push(*raiz);
    }

    while (!cola.empty()){

        nodo<c, T, comp>* nodo_actual = &(cola.front());
        cola.pop();

        resultado.push_back(nodo_actual->dato);

        if (nodo_actual->hijo_izquierdo != nullptr){
            cola.push(*(nodo_actual->hijo_izquierdo));
        }
        if (nodo_actual->hijo_derecho != nullptr){
            cola.push(*(nodo_actual->hijo_derecho));
        }
    }

    return resultado;
}

// Método público de ejecutar
template<typename c, typename T, bool (* comp)(c, c)>
void diccionario<c, T, comp>::ejecutar(std::function<void(T)> funcion) {
    ejecutar_recursivo(raiz, funcion);
}

// Método privado y recursivo de ejecutar
template<typename c, typename T, bool (* comp)(c, c)>
void diccionario<c, T, comp>::ejecutar_recursivo(nodo<c, T, comp>* nodo_actual, std::function<void(T)> funcion) {
    // Si el nodo es nulo, no hacer nada
    if (nodo_actual == nullptr) return;
    
    // Aplicar la función al dato del nodo actual
    funcion(nodo_actual->dato);

    // Recorrer el subárbol izquierdo
    ejecutar_recursivo(nodo_actual->hijo_izquierdo, funcion);
    
    // Recorrer el subárbol derecho
    ejecutar_recursivo(nodo_actual->hijo_derecho, funcion);
}

template<typename c, typename T, bool (* comp)(c, c)>
std::size_t diccionario<c, T, comp>::tamanio() {
    return cantidad_datos;
}

template<typename c, typename T, bool (* comp)(c, c)>
bool diccionario<c, T, comp>::vacio() {
    return cantidad_datos == 0;
}

//Su recursividad es multiple, directa y de cola.
template<typename c,typename T, bool (* comp)(c, c)>
void diccionario<c, T, comp>::borrar_ABB_recursivo(nodo<c, T, comp>* padre1){
    if (padre1 != nullptr){
        borrar_ABB_recursivo(padre1->hijo_izquierdo);
        borrar_ABB_recursivo(padre1->hijo_derecho);
        delete padre1;
    }
}

template<typename c, typename T, bool (* comp)(c, c)>
diccionario<c, T, comp>::~diccionario() {
    borrar_ABB_recursivo(raiz);
}

#endif