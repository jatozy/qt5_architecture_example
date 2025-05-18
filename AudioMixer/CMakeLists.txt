cmake_minimum_required(VERSION 3.14)
project(AudioMixer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(QT_QML_GENERATE_QMLLS_INI ON)

find_package(Qt5 REQUIRED COMPONENTS Core Qml Quick Widgets)

add_subdirectory(event_handler)
add_subdirectory(hardware)
add_subdirectory(hardware_interface)
add_subdirectory(main)
add_subdirectory(model)
add_subdirectory(persistency_interface)
add_subdirectory(persistency_filesystem)
add_subdirectory(store)
