#include "gmock/gmock.h"
#include "heap.hpp"

bool mayor(int a, int b) {
    return a > b;
}

class heap_test : public ::testing::Test {
protected:
    heap<int, mayor> heap1{};

    void SetUp() override;
};

void heap_test::SetUp() {
    heap1.alta(10);
    heap1.alta(7);
    heap1.alta(3);
    heap1.alta(13);
    heap1.alta(16);
    heap1.alta(11);
}

TEST_F(heap_test, alta) {
    heap1.alta(8);
    ASSERT_EQ(heap1.primero(), 16);
    ASSERT_EQ(heap1.tamanio(), 7);
    heap1.alta(20);
    ASSERT_EQ(heap1.primero(), 20);
    ASSERT_EQ(heap1.tamanio(), 8);
}

TEST_F(heap_test, baja) {
    ASSERT_EQ(heap1.baja(), 16);
    ASSERT_EQ(heap1.tamanio(), 5);
}

TEST_F(heap_test, baja_maneja_heap_vacio) {
    heap<int, mayor> heap2;
    EXPECT_THROW(heap2.baja(), heap_exception);
}

TEST_F(heap_test, primero) {
    ASSERT_EQ(heap1.primero(), 16);
}

TEST_F(heap_test, primero_maneja_heap_vacio) {
    heap<int, mayor> heap2;
    EXPECT_THROW(heap2.primero(), heap_exception);
}

TEST_F(heap_test, vacio) {
    heap<int, mayor> heap2;
    ASSERT_TRUE(heap2.vacio());
    heap2.alta(1);
    ASSERT_FALSE(heap2.vacio());
}

TEST_F(heap_test, tamanio) {
    ASSERT_EQ(heap1.tamanio(), 6);
}