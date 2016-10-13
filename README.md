# Bauasian
A modern OpenGL(core profile) based graphics engine using C++14 with boost.

master  
[![Build Status](https://travis-ci.org/karol-gruszczyk/graphics-engine.svg?branch=master)](https://travis-ci.org/karol-gruszczyk/graphics-engine)

develop  
[![Build Status](https://travis-ci.org/karol-gruszczyk/graphics-engine.svg?branch=develop)](https://travis-ci.org/karol-gruszczyk/graphics-engine)


## Build

### Requirements

#### Library
* GLEW
* GLM
* Boost
   * filesystem
* FreeImage
* Assimp
* FreeType

###### Ubuntu / Linux copy-paste
```bash
sudo apt-get install libglew-dev libglm-dev libboost-filesystem-dev libfreeimage-dev libassimp-dev libfreetype6-dev
```

#### Example usage program
* GLFW3

###### Ubuntu / Linux copy-paste
```bash
sudo apt-get install libglfw3-dev
```

### CMake
```bash
cmake .
make
```


## Utilized OpenGL features:
* Vertex Buffer Objects
* Vertex Array Objects
* Index Buffer Objects
* Frame Buffer Objects
* Render Buffer Objects
* Uniform Buffer Objects
* Direct State Access for
* Cube Textures
