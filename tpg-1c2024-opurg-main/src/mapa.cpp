#include "mapa.hpp"
#include <random>

int Generar_Numero_Aleatorio(int minimo, int maximo){
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distrib(minimo, maximo);
    return distrib(gen);
}

mapa::mapa() : casilleros_caminables{
        {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10}, {0, 11}, {0, 12}, {0, 13}, {0, 14}, {0, 15},
        {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8}, {1, 9}, {1, 10}, {1, 11}, {1, 12}, {1, 13}, {1, 14}, {1, 15},
        {2, 4}, {2, 5}, {2, 6}, {2, 14}, {2, 15},
        {3, 4}, {3, 5}, {3, 14}, {3, 15},
        {4, 4}, {4, 5}, {4, 14}, {4, 15},
        {5, 4}, {5, 5}, {5, 14}, {5, 15}, {5, 16}, {5, 19}, {5, 20},
        {6, 0}, {6, 1},{6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 14}, {6, 15}, {6, 16}, {6, 17}, {6, 18}, {6, 19}, {6, 20}, {6, 21},
        {7, 0}, {7, 1}, {7, 2}, {7, 3}, {7, 4}, {7, 5},{7, 6}, {7, 7}, {7, 8}, {7, 9}, {7, 10}, {7, 14}, {7, 15}, {7, 16}, {7, 17}, {7, 20}, {7, 21},
        {8, 0}, {8, 1}, {8, 4}, {8, 5}, {8, 6}, {8, 7}, {8, 8}, {8, 9}, {8, 10}, {8, 15}, {8, 16}, {8, 17}, {8, 20}, {8, 21},
        {9, 0}, {9, 1}, {9, 4}, {9, 5}, {9, 6}, {9, 9}, {9, 10}, {9, 15}, {9, 16}, {9, 17}, {9, 20}, {9, 21},
        {10, 0}, {10, 1}, {10, 4}, {10, 5}, {10, 6}, {10, 9}, {10, 10}, {10, 14}, {10, 15}, {10, 16}, {10, 17}, {10, 20}, {10, 21},
        {11, 0}, {11, 1}, {11, 2}, {11, 3}, {11, 4}, {11, 5}, {11, 6}, {11, 7}, {11, 8}, {11, 9}, {11, 10}, {11, 11}, {11, 12}, {11, 13}, {11, 14}, {11, 15}, {11, 16}, {11, 17}, {11, 18}, {11, 19}, {11, 20}, {11, 21}, {11, 22}, {11, 23},
        {12, 0}, {12, 1}, {12, 2}, {12, 3}, {12, 4}, {12, 5}, {12, 6}, {12, 7}, {12, 8}, {12, 9}, {12, 10}, {12, 11}, {12, 12}, {12, 13}, {12, 14}, {12, 15}, {12, 16}, {12, 17}, {12, 18}, {12, 19}, {12, 20}, {12, 21}, {12, 22}, {12, 23},
        {13, 4}, {13, 5}, {13, 6}, {13, 7}, {13, 8}, {13, 9}, {13, 10}, {13, 17}, {13, 18}, {13, 19}, {13, 20}, {13, 21},
        {14, 4}, {14, 5}, {14, 6}, {14, 7}, {14, 8}, {14, 9}, {14, 10},
        {15, 4}, {15, 5},
        {16, 3}, {16, 4}, {16, 5},
        {17, 3}, {17, 4}, {17, 5}
    }{
    mapa_completo = matriz(FILAS, COLUMNAS, PARED);

    for(const auto& casillero : casilleros_caminables){
        mapa_completo.modificar_elemento(casillero.first, casillero.second, CAMINABLE);
    }

    posiciones_locales = coordenadas_locales();
    posiciones_clientes = coordenadas_clientes();
}

coordenada mapa::generar_coordenadas_aleatoria(){
    coordenada coordenada_aleatoria = coordenada();
    if(!es_vecino_valido(coordenada_aleatoria)){
        int numero_aleatorio = Generar_Numero_Aleatorio( 0, 188);
        int x =  (int) casilleros_caminables[numero_aleatorio].first;
        int y =  (int) casilleros_caminables[numero_aleatorio].second;
        coordenada_aleatoria = coordenada(x, y);
    }
    return coordenada_aleatoria;
}

bool mapa::es_vecino_valido(coordenada posicion) {
    bool es_valido = false;
    if(posicion.x() >= 0 && posicion.x() < FILAS && posicion.y() >= 0 && posicion.y() < COLUMNAS){
        if(mapa_completo.elemento(posicion.x(), posicion.y()) == CAMINABLE){
            es_valido = true;
        }
    }
    return es_valido;
            
}

std::vector<coordenada> mapa::obtener_vecinos_validos(coordenada actual, coordenada destino) {
    std::vector<coordenada> vecinos;
    std::vector<coordenada> posibles_vecinos = {
        {actual.x() - 1, actual.y()},
        {actual.x() + 1, actual.y()},
        {actual.x(), actual.y() - 1},
        {actual.x(), actual.y() + 1}
    };

    for (auto& vecino : posibles_vecinos) {
        if (es_vecino_valido(vecino) || vecino == destino) {
            vecinos.push_back(vecino);
        }
    }

    return vecinos;
}


std::vector<coordenada> mapa::coordenadas_locales(){
    std::vector<coordenada> locales;
    int cantidad_locales = Generar_Numero_Aleatorio(MIN_LOCALES, MAX_LOCALES);
    for( int i = 0; i < cantidad_locales; i++){
        coordenada coordenada_local = generar_coordenadas_aleatoria();
        locales.push_back(coordenada_local);
        mapa_completo.modificar_elemento(coordenada_local.x(), coordenada_local.y(), LOCAL);
    }
    return locales;
}

std::vector<coordenada> mapa::obtener_posiciones_locales(){
    return posiciones_locales;
}

std::vector<coordenada> mapa::coordenadas_clientes(){
    std::vector<coordenada> clientes;
    int cantidad_clientes = Generar_Numero_Aleatorio(MIN_CLIENTES, MAX_CLIENTES);
    for(int i = 0; i < cantidad_clientes; i++){
        coordenada coordenada_cliente = generar_coordenadas_aleatoria();
        if(obtener_casilla(coordenada_cliente) != LOCAL){
            clientes.push_back(coordenada_cliente);
            mapa_completo.modificar_elemento(coordenada_cliente.x(), coordenada_cliente.y(), CLIENTE);
        }
    }
    return clientes;
}

void mapa::mover_clientes(){
    for(size_t i = 0; i < posiciones_clientes.size(); i++){
        mapa_completo.modificar_elemento(posiciones_clientes[i].first, posiciones_clientes[i].second, tipo_casilla::CAMINABLE);
    }

    posiciones_clientes.clear();
    posiciones_clientes = coordenadas_clientes();
}

tipo_casilla mapa::obtener_casilla(coordenada posicion){
    return mapa_completo.elemento(posicion.first, posicion.second);
}

size_t mapa::obtener_cant_locales() {
    return posiciones_locales.size();
}

void mapa::modificar_elemento_en_mapa(size_t fila, size_t columna, tipo_casilla tipo){
    mapa_completo.modificar_elemento(fila, columna, tipo);
}