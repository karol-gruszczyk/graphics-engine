# Bauasian
A modern OpenGL(core profile) based graphics engine using C++14 with boost.
![alt tag](https://lh6.googleusercontent.com/M1uMXluL5Cd0mKaPj-_AiMXe8sPUrz_UBSAu-Hkxuyx5JfMNDLxl09f8Qvwy686ZcXwEs9SkPcKWfg=w1366-h589)

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
* Vertex Buffers
* Vertex Arrays
* Index Buffers
* Frame Buffers
* Render Buffers
* Uniform Buffers
* Direct State Access
* Cube Textures
