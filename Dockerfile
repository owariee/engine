FROM ubuntu:latest

WORKDIR /engine

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update
RUN apt install -y build-essential
RUN apt install -y cmake
RUN apt install -y libxrandr-dev
RUN apt install -y libxinerama-dev
RUN apt install -y libxcursor-dev
RUN apt install -y libxi-dev
RUN apt install -y libgl-dev
RUN apt install -y mingw-w64
RUN apt install -y python
RUN update-alternatives --set x86_64-w64-mingw32-g++ /usr/bin/x86_64-w64-mingw32-g++-posix

CMD ./linux-windows-build.sh
