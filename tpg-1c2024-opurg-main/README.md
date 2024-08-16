[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/POWrYz7V)
# AyED / AYP2 - TPG 1c2024

<p align="center">
   <img src="Banner.jpg" alt="TPG: El bullicio del Callejon Aurum"><br>
</p>

## Nombre del grupo: opurG

### Integrantes:

#### Campos, Camilo - 109368

#### Guerrero, Steven - 110067

#### Moyano, Andrés - 110017

#### Petcoff, Tomás - 111498

#### Ardissone, Candela Rivero  - 110339

### Documentos:

1. [Informe de complejidad algorítmica](https://www.enlaceaca.com/)
2. [Video de demostración del programa](https://www.enlaceaca.com/)

### Compilación

El proyecto se puede compilar manualmente por terminal con la siguiente línea:

> g++ main.cpp -o main src/juego.cpp src/a_estrella/vertice.cpp src/a_estrella/a_estrella.cpp src/a_estrella/coordenada.cpp src/mapa.cpp src/aem/grafo.cpp src/aem/arista.cpp src/colores.cpp src/pedido.cpp src/local.cpp -Iinclude -Iinclude/a_estrella -Iinclude/aem -Wall -Wconversion -Werror 

O, alternativamente, con CMake, utilizando el archivo **CMakeLists.txt** presente en el directorio raíz.

Para distribuciones de Linux, se pueden utilizar los scripts presentes en el directorio raíz para compilar y ejecutar
la suite de tests. Requiere:

1. [g++](https://gcc.gnu.org/)
2. [CMake](https://cmake.org/)
3. [Valgrind](https://valgrind.org/)

Que se pueden instalar por terminal:

> sudo apt-get install // PROGRAMA //

# Aclaraciones adicionales:

El enlace a la carpeta en Google Drive con el video mostrando el funcionamiento del programa es el siguiente:
https://drive.google.com/drive/folders/1vu-OwhfMXvNuQ5QdoNloIa1dMlaG7UiY?usp=sharing

// ACLARACIONES ADICIONALES PARA EL CORRECTOR, COMO DECISIONES O SUPUESTOS QUE CONSIDERARON //