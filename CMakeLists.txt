cmake_minimum_required(VERSION 3.10)
project(node.ai)

set(CMAKE_CXX_STANDARD 17)

# Set source files
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/node/*.cpp
    src/ui/*.cpp
    imgui/*.cpp
    backends/*.cpp
)

add_executable(node.ai ${SOURCES})

# Include directories
target_include_directories(node.ai PRIVATE
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/backends
    ${CMAKE_SOURCE_DIR}/include/node
    ${CMAKE_SOURCE_DIR}/include/ui
)

# Link GLFW, OpenGL, etc.
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(node.ai PRIVATE
    OpenGL::GL
    glfw
)
