#include "gmock/gmock.h"
#include "diccionario.hpp"

bool menor(int a, int b) {
    return a < b;
}

class diccionario_test : public ::testing::Test {
protected:
    diccionario<int, int, menor> diccionario1{};
    std::vector<int> datos{};

    void SetUp() override;
};

void diccionario_test::SetUp() {
    diccionario1.alta(10, 10);
    diccionario1.alta(7, 7);
    diccionario1.alta(3, 3);
    diccionario1.alta(13, 13);
    diccionario1.alta(16, 16);
    diccionario1.alta(11, 11);
}

// Se usa inorder de forma arbitraria para rescatar todos los elementos.
TEST_F(diccionario_test, alta) {
    diccionario1.alta(8, 8);
    datos = diccionario1.inorder();
    ASSERT_THAT(datos, testing::ElementsAre(3, 7, 8, 10, 11, 13, 16));
    ASSERT_EQ(datos.size(), 7);
}

TEST_F(diccionario_test, alta_maneja_clave_repetida) {
    EXPECT_THROW(diccionario1.alta(10, 10), diccionario_exception);
}

TEST_F(diccionario_test, operador_acceso) {
    ASSERT_EQ(diccionario1[10], 10);
}

TEST_F(diccionario_test, operador_acceso_maneja_clave_no_existente) {
    EXPECT_THROW(diccionario1[8], diccionario_exception);
}

TEST_F(diccionario_test, inorder) {
    datos = diccionario1.inorder();
    ASSERT_THAT(datos, testing::ElementsAre(3, 7, 10, 11, 13, 16));
}

TEST_F(diccionario_test, preorder) {
    datos = diccionario1.preorder();
    ASSERT_THAT(datos, testing::ElementsAre(10, 7, 3, 13, 11, 16));
}

TEST_F(diccionario_test, postorder) {
    datos = diccionario1.postorder();
    ASSERT_THAT(datos, testing::ElementsAre(3, 7, 11, 16, 13, 10));
}

TEST_F(diccionario_test, ancho) {
    datos = diccionario1.ancho();
    ASSERT_THAT(datos, testing::ElementsAre(10, 7, 13, 3, 11, 16));
}

TEST_F(diccionario_test, tamanio) {
    ASSERT_EQ(diccionario1.tamanio(), 6);
}

TEST_F(diccionario_test, vacio) {
    diccionario<int, int, menor> diccionario2;
    ASSERT_TRUE(diccionario2.vacio());
    diccionario2.alta(1, 1);
    ASSERT_FALSE(diccionario2.vacio());
}

TEST_F(diccionario_test, baja) {
    diccionario1.baja(10);
    ASSERT_THAT(diccionario1.inorder(), testing::ElementsAre(3, 7, 11, 13, 16));
    ASSERT_THAT(diccionario1.preorder(), testing::ElementsAre(11, 7, 3, 13, 16));
    ASSERT_THAT(diccionario1.postorder(), testing::ElementsAre(3, 7, 16, 13, 11));
    ASSERT_THAT(diccionario1.ancho(), testing::ElementsAre(11, 7, 13, 3, 16));
    ASSERT_EQ(diccionario1.tamanio(), 5);

    diccionario1.baja(13);
    ASSERT_THAT(diccionario1.inorder(), testing::ElementsAre(3, 7, 11, 16));
    ASSERT_THAT(diccionario1.preorder(), testing::ElementsAre(11, 7, 3, 16));
    ASSERT_THAT(diccionario1.postorder(), testing::ElementsAre(3, 7, 16, 11));
    ASSERT_THAT(diccionario1.ancho(), testing::ElementsAre(11, 7, 16, 3));
    ASSERT_EQ(diccionario1.tamanio(), 4);

    diccionario1.baja(16);
    ASSERT_THAT(diccionario1.inorder(), testing::ElementsAre(3, 7, 11));
    ASSERT_THAT(diccionario1.preorder(), testing::ElementsAre(11, 7, 3));
    ASSERT_THAT(diccionario1.postorder(), testing::ElementsAre(3, 7, 11));
    ASSERT_THAT(diccionario1.ancho(), testing::ElementsAre(11, 7, 3));
    ASSERT_EQ(diccionario1.tamanio(), 3);

    diccionario1.baja(1);
    ASSERT_THAT(diccionario1.inorder(), testing::ElementsAre(3, 7, 11));
    ASSERT_THAT(diccionario1.preorder(), testing::ElementsAre(11, 7, 3));
    ASSERT_THAT(diccionario1.postorder(), testing::ElementsAre(3, 7, 11));
    ASSERT_THAT(diccionario1.ancho(), testing::ElementsAre(11, 7, 3));
    ASSERT_EQ(diccionario1.tamanio(), 3);
}