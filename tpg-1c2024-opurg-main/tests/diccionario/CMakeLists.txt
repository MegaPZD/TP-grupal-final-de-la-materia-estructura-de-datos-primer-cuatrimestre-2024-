project(diccionario_test)

add_executable(diccionario_test
        diccionario_test.cpp
)

target_link_libraries(
        diccionario_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(diccionario_test)