project(grafo_test)

add_executable(grafo_test
        grafo_test.cpp
)

target_link_libraries(
        grafo_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(grafo_test)