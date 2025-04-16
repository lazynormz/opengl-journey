project(game)

add_executable(game
    src/main.cpp
)

target_include_directories(game PRIVATE
    ../engine/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(game
    PRIVATE
        engine
)

add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "D:/cpp-libs/SDL3/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:game>
)