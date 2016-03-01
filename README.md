# graphics-engine
A modern OpenGL based graphics engine using modern C++14 with boost.

## Setup
```bash
git clone --recursive git@github.com:karol-gruszczyk/graphics-engine.git
cd graphics-engine/
```

* Boost
`cl.exe` and `link.exe` need to be added to the **PATH** enviroment variable
```bash
cd libs/boost/
./boostrap.sh
./b2
```

* GLEW

For windows it is recommended to download the latest binaries from https://github.com/nigels-com/glew#downloads and place the `bin`, `lib` and `include` directory into `libs/glew`
