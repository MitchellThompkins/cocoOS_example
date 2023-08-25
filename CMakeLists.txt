cmake_minimum_required(VERSION 3.22)

#add_subdirectory(c)

project(cocoOS_example
    LANGUAGES C
)

option(FORCE_COLORED_OUPTUT "Always produce ANSI-colored output" ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_C_FLAGS "-g -O0 -save-temps --std=gnu99")

# Print more options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_EXECUTABLE_SUFFIX_C .elf)

include(FetchContent)
FetchContent_Declare(
    cocoOS
    GIT_REPOSITORY https://github.com/MitchellThompkins/cocoOS
    GIT_TAG        develop
)

FetchContent_MakeAvailable(cocoOS)

add_library(user_os_config INTERFACE)
target_include_directories(user_os_config
    INTERFACE
        c/include
)

add_executable(cocoOS_example_c
    c/src/main.c
)

target_link_libraries(cocoOS_example_c
    pthread
    cocoOs
)
