cmake_minimum_required(VERSION 4.0)
project(raygui CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force X11 (safe for your system)
set(ENV{GDK_BACKEND} x11)
set(ENV{SDL_VIDEODRIVER} x11)
set(ENV{QT_QPA_PLATFORM} xcb)
set(ENV{GLFW_PLATFORM} x11)

# System raylib (YOU installed this)
find_package(raylib REQUIRED)

# Source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp"
)

# Executable
add_executable(${PROJECT_NAME}
        sources/text_editor.cpp
)

# Include dirs
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/sources
)

# Link raylib
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)