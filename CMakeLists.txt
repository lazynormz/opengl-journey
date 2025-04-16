#Give me a basic setup for a C++20 project using CMake

cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME MyProgram)
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SHADERS_SRC_DIR "${CMAKE_SOURCE_DIR}/src/shaders")
set(SHADERS_DST_DIR "${CMAKE_BINARY_DIR}/Debug/shaders")

set(SHADER_FILES
    "${SHADERS_SRC_DIR}/shader.vert"
    "${SHADERS_SRC_DIR}/shader.frag"
)

set(SOURCES
    src/main.cpp
    src/game.cpp
    src/shaderProgram.cpp
    src/mesh.cpp
)

set(HEADERS
    src/game.hpp
    src/shaderProgram.hpp
    src/mesh.hpp
    src/tinyUtil.hpp
    src/gameState.hpp
)

set(SDL_INCLUDE_DIR "D:/cpp-libs/SDL3/include")
set(SDL_LIB_DIR "D:/cpp-libs/SDL3/lib/x64")

set(GLAD_ROOT "D:/cpp-libs/glad")

add_library(glad STATIC 
    ${GLAD_ROOT}/src/glad.c
)
target_include_directories(glad PUBLIC ${GLAD_ROOT}/include)

include_directories("D:/cpp-libs/glm-1.0.1")
include_directories(${CMAKE_SOURCE_DIR}/external)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${CMAKE_SOURCE_DIR}/external/tiny_gltf.cc)

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
    glad
    ${SDL_LIB_DIR}/SDL3.lib
    opengl32
)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLAD_GL_IMPLEMENTATION)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL_LIB_DIR}/SDL3.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Make sure destination directory exists
file(MAKE_DIRECTORY ${SHADERS_DST_DIR})

foreach(SHADER_FILE ${SHADER_FILES})
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SHADER_FILE}
            ${SHADERS_DST_DIR}
        COMMENT "Copying shader: ${SHADER_FILE}"
    )
endforeach()