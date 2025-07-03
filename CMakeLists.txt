cmake_minimum_required(VERSION 3.10)
project(ImGuiApp)

set(CMAKE_CXX_STANDARD 17)

# Set source files
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/node/*.cpp
    imgui/*.cpp
    backends/*.cpp
)

add_executable(ImGuiApp ${SOURCES})

# Include directories
target_include_directories(ImGuiApp PRIVATE
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/backends
    ${CMAKE_SOURCE_DIR}/include/node
)

# Link GLFW, OpenGL, etc.
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(ImGuiApp PRIVATE
    OpenGL::GL
    glfw
)
