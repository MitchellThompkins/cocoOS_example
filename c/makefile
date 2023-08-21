.PHONY: build
build:
	mkdir -p build \
	&& cd build/ \
	&& cmake .. \
	&& cmake --build .

.PHONY: clean
clean:
	rm -rf build

.PHONY: container.pull
container.pull:
	docker pull ghcr.io/mitchellthompkins/embedded_sdk:latest

.PHONY: container.start
container.start:
	docker-compose -f docker-compose.yml run --rm dev_env 'sh -x'

