
set(COMPONENT_NAME "persistency_interface")
set(LIBRARY_NAME "jatozy_mixer_${COMPONENT_NAME}")

set(SOURCES_CPP
)

set(SOURCES_H
)

set(PUBLIC_HEADER_FOLDERS
    include
)

set(PRIVATE_HEADER_FOLDERS
    src
)

add_library(${LIBRARY_NAME} INTERFACE
    ${SOURCES_CPP}
    ${SOURCES_H}
)

target_include_directories(${LIBRARY_NAME}
    INTERFACE
        ${PUBLIC_HEADER_FOLDERS}
)

target_link_libraries(${LIBRARY_NAME}
    INTERFACE
        jatozy::mixer::model
)

set_target_properties(${LIBRARY_NAME} PROPERTIES
    AUTOMOC ON
    POSITION_INDEPENDENT_CODE ON
)

add_library(jatozy::mixer::${COMPONENT_NAME} ALIAS ${LIBRARY_NAME})