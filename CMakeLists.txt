cmake_minimum_required(VERSION 3.16)
project(OOP_AP)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE ALL_CPP_FILES
        "${CMAKE_SOURCE_DIR}/*.cpp"
)

foreach(CPP_FILE IN LISTS ALL_CPP_FILES)
    get_filename_component(TARGET_NAME ${CPP_FILE} NAME_WE)
    add_executable(${TARGET_NAME} ${CPP_FILE})
endforeach()
