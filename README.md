# Cybertruck 3D Viewer

A simple OpenGL-based 3D model viewer built in C++, using a custom OBJ loader to render a Cybertruck model.

## Files

- `main.cpp` — entry point, sets up the OpenGL context and render loop
- `objloader.cpp` / `objloader.hpp` — custom loader for parsing `.obj` model files
- `cybertruck.obj` / `cybertruck.mtl` — the 3D model and its material definitions
- `tri.obj` — simple test geometry
- `Makefile` — build configuration

## Build

```
make
```

## Run

```
./cybertruck_viewer
```

## Requirements

- C++ compiler (g++ or clang)
- OpenGL development libraries installed on your system
