qt5_add_resources(QML_RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../qml/qml.qrc
)

add_executable(AudioApp main.cpp ${QML_RESOURCES})

target_link_libraries(AudioApp
    Qt5::Core
    Qt5::Quick
    Qt5::Qml
    jatozy::mixer::hardware
    jatozy::mixer::model
    jatozy::mixer::store
    jatozy::mixer::event_handler
    jatozy::mixer::persistency_filesystem
)