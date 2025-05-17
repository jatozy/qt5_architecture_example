FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y sudo wget git build-essential cmake clang mesa-common-dev qtbase5-dev qt5-qmake libqt5qml5 libqt5qmlmodels5 libqt5qmlworkerscript5 qtdeclarative5-dev

RUN echo "ubuntu ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

RUN apt-get upgrade -y

USER ubuntu