CC = gcc
TARGET = cocoOS_example_c

.PHONY: build.cmake
build.cmake:
	mkdir -p cmake_build \
	&& cd cmake_build/ \
	&& cmake .. \
	&& cmake --build .

.PHONY: build.makefile
build.makefile:
	$(CC) $(CFLAGS) -o $(TARGET) src/main.c ../cocoOS/os/cocoos/src/*.c -I include/ -I ../cocoOS/os/cocoos/include/

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

