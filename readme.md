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
