FROM ubuntu:latest

WORKDIR /work

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update
RUN apt install -y build-essential
RUN apt install -y cmake
RUN apt install -y git
RUN apt install -y libxrandr-dev
RUN apt install -y libxinerama-dev
RUN apt install -y libxcursor-dev
RUN apt install -y libxi-dev
RUN apt install -y libgl-dev
RUN apt install -y mingw-w64
RUN apt install -y python

RUN git clone https://github.com/owariee/engine.git

WORKDIR /work/engine
RUN git submodule update --init --recursive
RUN mkdir build

WORKDIR /work/engine/build
RUN cmake -DCMAKE_TOOLCHAIN_FILE=../externals/mingw-w64/mingw-w64-x86_64.cmake ..
RUN make
