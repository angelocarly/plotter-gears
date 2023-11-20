set(
    HEADER_FILES
        MeshPresenter.h
)

set(
    SOURCE_FILES
        Source/MeshPresenter.cpp
        main.cpp
)

set(
    GLSL_SOURCE_FILES
        shaders/Mesh.frag
        shaders/Mesh.vert
)

add_executable(
    Grs
        ${SOURCE_FILES}
        ${HEADER_FILES}
)

set_property( TARGET Grs PROPERTY CXX_STANDARD 17 )

## Project libraries
target_link_libraries(
        Grs PUBLIC
        Burst
)

include_directories( ${BURST_ROOT_DIR} )

compile_shaders( Grs "${CMAKE_SOURCE_DIR}/resources/" "${CMAKE_CURRENT_BINARY_DIR}/resources/shaders/" "${GLSL_SOURCE_FILES}" )
