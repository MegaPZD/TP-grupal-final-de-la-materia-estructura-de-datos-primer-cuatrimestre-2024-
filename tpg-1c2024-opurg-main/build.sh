#!/bin/bash
if [ ! -d "build" ]; then
  mkdir build
fi
cd build && cmake ..
if ! cmake --build .; then
  echo "ERROR: El proyecto no compiló correctamente. Revisá los errores que aparecen arriba."
  exit 1
else
  echo "El proyecto compiló correctamente."
fi