#!/bin/bash
if [ ! -d "build" ]; then
  echo "ERROR: No se compiló el proyecto. Ejecutá './build.sh' antes de probar."
  exit 1
elif [ ! -f "build/tests/diccionario_test" ] || [ ! -f "build/tests/heap_test" ]; then
  echo "ERROR: El proyecto no compiló correctamente. Revisá los errores que reporta './build.sh'."
  exit 1
else
  if ! valgrind --leak-check=yes --error-exitcode=1 ./build/tests/diccionario_test ||
  ! valgrind --leak-check=yes --error-exitcode=1 ./build/tests/heap_test; then
    exit 1
  fi
fi