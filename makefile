# Specify the build parameters
CC = gcc
CFLAGS = -g -O0 -save-temps --std=gnu99
TARGET = cocoOS_example_c

# Specify the path to these source files relative to the build directory
COCOOS_SRC = ../cocoOS/os/os_event/src/*.c \
			 ../cocoOS/os/os_kernel/src/*.c \
			 ../cocoOS/os/os_msgqueue/src/*.c \
			 ../cocoOS/os/os_sem/src/*.c \
			 ../cocoOS/os/os_task/src/*.c \
			 ../cocoOS/os/os_utils/src/*.c

# Specify the path to these header files relative to the build directory
COCOOS_INCLUDE = -I../cocoOS/os/cocoos/include/ \
				 -I../cocoOS/os/os_event/include/ \
			 	 -I../cocoOS/os/os_kernel/include/ \
			 	 -I../cocoOS/os/os_msgqueue/include/ \
			 	 -I../cocoOS/os/os_sem/include/ \
			 	 -I../cocoOS/os/os_task/include/ \
			 	 -I../cocoOS/os/os_utils/include/

.PHONY: build.makefile
build.makefile:
	mkdir -p makefile_build \
	&& cd makefile_build/ \
	&& $(CC) $(CFLAGS) -I../c/include $(COCOOS_INCLUDE) -o $(TARGET).elf ../c/src/main.c $(COCOOS_SRC) -lpthread

.PHONY: build.cmake
build.cmake:
	mkdir -p cmake_build \
	&& cd cmake_build/ \
	&& cmake .. \
	&& cmake --build .

.PHONY: clean
clean:
	rm -rf cmake_build
	rm -rf makefile_build

.PHONY: container.pull
container.pull:
	docker pull ghcr.io/mitchellthompkins/embedded_sdk:latest

.PHONY: container.start
container.start:
	docker-compose -f docker-compose.yml run --rm dev_env 'sh -x'

