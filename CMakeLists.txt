cmake_minimum_required(VERSION 3.14)

project(MyQtApp VERSION 1.0 LANGUAGES CXX)

find_package(Qt5 COMPONENTS Qml Quick Test REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    main.cpp
    )
# Hauptprogramm
add_executable(${PROJECT_NAME} ${SOURCES})

# Qt Widgets hinzufügen
target_link_libraries(${PROJECT_NAME} Qt5::Qml Qt5::Quick)

# Qt MOC, UIC, RCC automatisch verarbeiten
set_target_properties(MyQtApp PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
)