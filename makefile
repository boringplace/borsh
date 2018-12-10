.PHONY: clean

all: borsh

borsh: CMakeLists.txt
	mkdir -p build
	(cd build && cmake  ..)
	(cd build && make)

clean:
	git clean -fdx

