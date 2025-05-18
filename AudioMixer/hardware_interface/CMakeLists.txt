
set(COMPONENT_NAME "hardware_interface")
set(LIBRARY_NAME "jatozy_mixer_${COMPONENT_NAME}")

set(SOURCES_CPP
    src/Hardware.cpp
)

set(SOURCES_H
    include/jatozy/hardware_interface/Factory.h
    include/jatozy/hardware_interface/Hardware.h
)

set(PUBLIC_HEADER_FOLDERS
    include
)

set(PRIVATE_HEADER_FOLDERS
    src
)

add_library(${LIBRARY_NAME} STATIC
    ${SOURCES_CPP}
    ${SOURCES_H}
)

target_include_directories(${LIBRARY_NAME}
    INTERFACE
        ${PUBLIC_HEADER_FOLDERS}
    PRIVATE
        ${PUBLIC_HEADER_FOLDERS}
        ${PRIVATE_HEADER_FOLDERS}
)

target_link_libraries(${LIBRARY_NAME}
    PUBLIC
        Qt5::Core
)

set_target_properties(${LIBRARY_NAME} PROPERTIES
    AUTOMOC ON
    POSITION_INDEPENDENT_CODE ON
)

add_library(jatozy::mixer::${COMPONENT_NAME} ALIAS ${LIBRARY_NAME})