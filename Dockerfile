FROM ubuntu:latest

WORKDIR /engine

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update
RUN apt install -y build-essential
RUN apt install -y cmake
RUN apt install -y libglfw3-dev
RUN apt install -y libopenal-dev
RUN apt install -y libglm-dev
RUN apt install -y mingw-w64
RUN apt install -y python
RUN update-alternatives --set x86_64-w64-mingw32-g++ /usr/bin/x86_64-w64-mingw32-g++-posix

CMD ./linux-windows-build.sh
