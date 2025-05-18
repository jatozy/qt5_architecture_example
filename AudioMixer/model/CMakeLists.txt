set(COMPONENT_NAME "model")
set(LIBRARY_NAME "jatozy_mixer_${COMPONENT_NAME}")

set(SOURCES_CPP
    src/Amp.cpp
    src/AmpD10.cpp
    src/AmpD10Model.cpp
    src/UndoStackModel.cpp
)

set(SOURCES_H
    include/jatozy/model/Amp.h
    include/jatozy/model/AmpD10.h
    include/jatozy/model/AmpD10Model.h
    include/jatozy/model/UndoStackModel.h
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
    PRIVATE
        jatozy::mixer::hardware_interface
)

set_target_properties(${LIBRARY_NAME} PROPERTIES
    AUTOMOC ON
    POSITION_INDEPENDENT_CODE ON
)

add_library(jatozy::mixer::${COMPONENT_NAME} ALIAS ${LIBRARY_NAME})