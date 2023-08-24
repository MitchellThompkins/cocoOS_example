# Introduction

This serves to showcase an example of building a project which relies on the
cocoOS cooperative scheduler. Building with CMake is supported (and indeed
encouraged) but you can also simply include the OS directly into your project
(shown here by using a git submodule).

# Building

## Open the container
You will need docker isntalled, although if you have the required cmake version
(or you are not building with cmake) and gcc compiler you can build locally and
skip this step.


Get and drop into the docker container
```bash
make container.pull
make container.start
```
## With CMake
Refer to the `CMakeLists.txt` file in this directory. The relevant sections to
add to your CMake project are shown below:

```
include(FetchContent)
FetchContent_Declare(
    cocoOS
    GIT_REPOSITORY https://github.com/MitchellThompkins/cocoOS
    GIT_TAG        test_user_dependency
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

```

To build this example with CMake execute the below function.

```bash
make build.cmake
```
## With Makefile
You will need to specify all of the source and include files. The `makefile` in
this directory has an example of how to do this.

To build this example with just a makefile execute the below function.
```bash
make build.makefile
```

# Running
```bash
sh-4.4$ ./cmake_build/cocoOS_example_c.elf
+ ./cmake_build/cocoOS_example_c.elf

hello world
bar
foo
foobar
global_time: 0
global_time: 1
global_time: 2
global_time: 3
after foobar
global_time: 4
global_time: 5

sh-4.4$ ./makefile_build/cocoOS_example_c.elf
+ ./makefile_build/cocoOS_example_c.elf

hello world
bar
foo
foobar
global_time: 0
global_time: 1
global_time: 2
global_time: 3
after foobar
global_time: 4
global_time: 5
```
