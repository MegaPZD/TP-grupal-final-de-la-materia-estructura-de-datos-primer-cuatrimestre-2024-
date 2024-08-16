#include "juego.hpp"
#include <string>
#include <stack>
#include <iostream>
#include <random>

bool comp_nombre(std::string local1, std::string local2){
    return local1 < local2;
}

int generador_pedido(int minimo, int maximo){
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distrib(minimo, maximo);
    return distrib(gen);
}

int juego::generar_numero_random_excluyente(int exclude) {
    std::vector<int> numeros;
    for (size_t i = 1; i <= mapa1.obtener_cant_locales(); ++i) {
        if (int(i) != exclude) {
            numeros.push_back(int(i));
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, (int)numeros.size() - 1);

    return numeros[distr(gen)];
}


local juego::crear_local(std::vector<coordenada> ubicacion_locales, size_t cant_locales) {
    coordenada ubicacion = ubicacion_locales[cant_locales-1];
    std::string nombre = "local" + std::to_string(cant_locales);

    return local(nombre, ubicacion, cant_locales);
}

void juego::asignar_pedidos_arista(local* origen, local destino) {
    size_t peso_pedido = size_t (generador_pedido(MIN_PESO_PEDIDO, MAX_PESO_PEDIDO));
    origen->crear_pedido(*origen, destino, peso_pedido, origen->prioridad_local());
    //Nota: la prioridad del local = al número n la clave del local ("localn")
    minijuego2.modificar_arista((origen->prioridad_local()) -1, (destino.prioridad_local()) -1, (int)peso_pedido);
}

void juego::listado_pedidos(local* origen) {
    int cantidad_pedidos = generador_pedido(MIN_CANT_PEDIDO, MAX_CANT_PEDIDO);
    for (int i = 0; i < cantidad_pedidos; ++i) {
        int numero_aleatorio = generar_numero_random_excluyente(int (origen->prioridad_local()));
        asignar_pedidos_arista(origen, locales["local"+ to_string(numero_aleatorio)]);
    }
}


juego::juego() : mapa1(), locales(), minijuego1(), minijuego2(){
    minijuego2 = grafo(mapa1.obtener_cant_locales());
    for (size_t i = 1; i <= mapa1.obtener_cant_locales(); ++i) {
        local local_aux = crear_local(mapa1.obtener_posiciones_locales(), i);
        locales.alta(local_aux.obtener_nombre(), local_aux);
    }

    for (size_t i = 1; i <= mapa1.obtener_cant_locales(); ++i) {
        listado_pedidos(&(locales["local" + to_string(i)]));
        pedido p = locales["local" + to_string(i)].obtener_pedido_prioritario();
    }
}

void juego::actualizar_mapa_con_camino_actual(std::stack<coordenada> camino, coordenada origen, coordenada destino){
    if(!(camino.empty())){
        camino.pop();
        coordenada actual = camino.top();
        while(!(camino.empty())){
            if(camino.top() != origen || camino.top() != destino){
                mapa1.modificar_elemento_en_mapa(actual.x(), actual.y(), tipo_casilla::CAMINADO);
            }
            if(!(camino.empty())){
                actual = camino.top();
                camino.pop();
            }
        }
    }
}

int distancia_manhattan(vertice* destino, vertice* actual) {
    coordenada distancia = *destino - *actual;
    return std::abs(distancia.x()) + std::abs(distancia.y());
}

void juego::resolver_minijuegos(local local1){

    pedido pedido_prioritario = local1.obtener_pedido_prioritario();
    coordenada origen = pedido_prioritario.obtener_origen();
    coordenada destino = pedido_prioritario.obtener_destino();

    while(local1.tamanio_del_heap_actual() > 1){
        std::cout << std::endl;
        imprimir_mapa();
        std::stack<coordenada> camino = minijuego1.obtener_camino_minimo(pedido_prioritario.obtener_origen(), pedido_prioritario.obtener_destino(), mapa1, distancia_manhattan);
        actualizar_mapa_con_camino_actual(camino, origen, destino);
        std::cout << std::endl;
        imprimir_mapa();
        reiniciar_mapa();

        if(local1.tamanio_del_heap_actual() > 1){
            local1.eliminar_pedido_prioritario();
            pedido_prioritario = local1.obtener_pedido_prioritario();
            origen = pedido_prioritario.obtener_origen();
            destino = pedido_prioritario.obtener_destino();
        }
    }
}

void juego::resolver(){
    locales.ejecutar([this](local local1) { this->resolver_minijuegos(local1); });
    std::vector<arista> aem = minijuego2.obtener_aem();
    for(size_t i = 0; i < aem.size(); i++){
        std::pair<size_t, size_t> vectice_transitado = aem[i].obtener_vertices();
        std::cout << "Peso de arista maxima: " << aem[i].obtener_peso() << ". Conecta los vertices: (" << vectice_transitado.first << " , " << vectice_transitado.second << ")\n";
    }
}

void juego::imprimir_mapa() {
    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            colores::imprimir_casilla(colores::obtener_color_segun_tipo(mapa1.obtener_casilla(coordenada(i, j))));
        }
        std::cout << std::endl;
    }
}

void juego::reiniciar_mapa(){
    for(size_t i = 0; i < FILAS; i++){
        for (size_t j = 0; j < COLUMNAS; j++){
            coordenada posicion(static_cast<int>(i),static_cast<int>(j));
            if (mapa1.obtener_casilla(posicion) == tipo_casilla::CAMINADO){
                mapa1.modificar_elemento_en_mapa(i,j, tipo_casilla::CAMINABLE);
            }
            
        }
    mapa1.mover_clientes();
    }
}