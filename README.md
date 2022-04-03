# 🧊 Engine

This is an engine in development, by now we have an opengl graphics backend.
Feel free to contribute!!

## Cloning the repo

`git clone git@github.com:owariee/engine.git`

### Updating submodules

`git submodule update --init --recursive`

## Building

### Ubuntu dependencies when building libraries from source (default behaviour)

```
sudo apt install -y build-essential cmake libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl-dev python
```

### Building

Inside the repository after clone(see `Cloning the repo`), execute these commands:

```
#!/usr/bin/env bash
mkdir build
cd build
cmake ..
make
```

You can also create a file called build.sh and paste the content described, then
give the right permissions with `chmod +x build.sh` and execute `./build.sh`.

### Cross-platform development build with Docker

1. Build the image

`docker build -t engine:dev0 .`

2. Run the container (this will compile the project)

`docker run -t -v $(pwd):/engine engine:dev0`

## Development

The project can be built against its dependencies statically or dynamically,
but when using static dependencies, it will, necessarily, build the dependency
from source, but if the dinamic dependencies are chosen, the engine can be built
against the system native libraries, in UNIX systems, which saves compilation time,
and allows the system to use native libraries, or, if the system doesn't provide
that dependency, then it can be built from the external dependencies and then
linked dinamically against the engine. On non-UNIX systems, even the dinamic
dependencies will be built from source.

The variable that controls this behaviour is BUILD_STATIC, and it defaults to FALSE.

![BUILD_STATIC usage example](/doc/BUILD_STATIC_EXAMPLE.jpg)

### Libraries used in this project

1. GLFW
2. OpenAL Soft
4. GLAD
5. GLM
6. ImGUI
8. Miniz
