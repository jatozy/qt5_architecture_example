set(COMPONENT_NAME "store")
set(LIBRARY_NAME "jatozy_mixer_${COMPONENT_NAME}")

set(SOURCES_CPP
    src/State.cpp
    src/Store.cpp
    )
    
set(SOURCES_H
    include/jatozy/store/State.h
    include/jatozy/store/Store.h
    include/jatozy/store/commands/AddAmp.h
    include/jatozy/store/commands/MuteAllAmps.h
    include/jatozy/store/commands/SetGainAmp.h
    include/jatozy/store/commands/ToggleMuteAmp.h
    include/jatozy/store/commands/UnmuteAllAmps.h
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
        Qt5::Widgets
        jatozy::mixer::model
    PRIVATE
        jatozy::mixer::hardware_interface
        jatozy::mixer::persistency_interface
)

set_target_properties(${LIBRARY_NAME} PROPERTIES
    AUTOMOC ON
    POSITION_INDEPENDENT_CODE ON
)

add_library(jatozy::mixer::${COMPONENT_NAME} ALIAS ${LIBRARY_NAME})