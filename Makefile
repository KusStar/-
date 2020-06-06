detault_target: all
.PHONY : default_target

all: config run

config:
	cmake -B./build/
.PHONY : config

run:
	cmake --build ./build
	./build/run
.PHONY : run
