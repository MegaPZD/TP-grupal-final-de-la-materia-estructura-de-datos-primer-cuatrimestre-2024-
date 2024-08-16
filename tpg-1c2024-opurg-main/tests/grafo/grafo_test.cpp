#include "gmock/gmock.h"
#include "grafo.hpp"

class grafo_test : public ::testing::Test {
protected:
    grafo grafo1;
    std::vector<arista> aem;

    void SetUp() override;
};

void grafo_test::SetUp() {
    grafo1 = grafo(4);
    grafo1.modificar_arista(0, 1, 3);
    grafo1.modificar_arista(1, 0, 3);
    grafo1.modificar_arista(0, 2, 4);
    grafo1.modificar_arista(2, 0, 4);
    grafo1.modificar_arista(0, 3, 2);
    grafo1.modificar_arista(3, 0, 2);
    grafo1.modificar_arista(1, 2, 6);
    grafo1.modificar_arista(2, 1, 6);
    grafo1.modificar_arista(1, 3, 5);
    grafo1.modificar_arista(3, 1, 5);
    grafo1.modificar_arista(2, 3, 1);
    grafo1.modificar_arista(3, 2, 1);
}

TEST_F(grafo_test, arbol_expansion_maxima) {
    aem = grafo1.obtener_aem();
    ASSERT_EQ(aem.size(), 3);

    int costo = 0;
    for (arista& arista: aem) {
        costo += arista.obtener_peso();
    }
    ASSERT_EQ(costo, 15);

    std::vector<std::pair<size_t, size_t>> vertices_esperados = {{0, 2},
                                                                 {1, 2},
                                                                 {1, 3}};
    for (std::pair<size_t, size_t>& vertices: vertices_esperados) {
        auto es_arista = [vertices](arista a) { return a == vertices; };
        auto it = std::find_if(aem.begin(), aem.end(), es_arista);
        ASSERT_TRUE(it != aem.end());
    }
}