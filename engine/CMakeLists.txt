project(engine)

set(ENGINE_SOURCE 
    src/engine.cpp
    src/mesh.cpp
    src/shaderProgram.cpp
    src/camera.cpp
    external/tiny_gltf.cc
)

set(ENGINE_HEADERS
    include/engine.hpp
    include/mesh.hpp
    include/gameState.hpp
    include/shaderProgram.hpp
    include/tinyUtil.hpp
    include/camera.hpp
    external/json.hpp
    external/tiny_gltf.h
)

set(SHADERS_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders")
set(SHADERS_DST_DIR "${CMAKE_BINARY_DIR}/game/Debug/shaders")

set(SHADER_FILES
    "${SHADERS_SRC_DIR}/shader.vert"
    "${SHADERS_SRC_DIR}/shader.frag"
)

set(GLAD_ROOT "D:/cpp-libs/glad")

add_library(engine STATIC ${ENGINE_SOURCE} ${ENGINE_HEADERS} ${GLAD_ROOT}/src/glad.c)

set(SDL_INCLUDE_DIR "D:/cpp-libs/SDL3/include")
set(SDL_LIB_DIR "D:/cpp-libs/SDL3/lib/x64")

set(GLM_ROOT "D:/cpp-libs/glm-1.0.1")

target_include_directories(engine 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${GLAD_ROOT}/include
        ${SDL_INCLUDE_DIR}
        ${GLM_ROOT}
        external
)

target_link_libraries(engine
    PUBLIC
        ${SDL_LIB_DIR}/SDL3.lib
        opengl32
)

target_compile_definitions(engine PRIVATE GLAD_GL_IMPLEMENTATION)

file(MAKE_DIRECTORY ${SHADERS_DST_DIR})

foreach(SHADER_FILE ${SHADER_FILES})
    add_custom_command(
        TARGET engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SHADER_FILE}
            ${SHADERS_DST_DIR}
        COMMENT "Copying shader: ${SHADER_FILE}"
    )
endforeach()