FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
    sudo wget git build-essential cmake gdb vim\
    clang clang-format\
    mesa-common-dev \
    qtbase5-dev qt5-qmake libqt5qml5 libqt5qmlmodels5 \
    libqt5qmlworkerscript5 \
    qtdeclarative5-dev qt5-quick-demos

RUN echo "ubuntu ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

RUN apt-get upgrade -y

USER ubuntu