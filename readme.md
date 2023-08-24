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
```bash
make build.cmake
```
## With Makefile

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
