.PHONY: default
default: test;

compile:
	g++ main.cpp lodepng.cpp -o test -O2

test: compile
	./test

clean:
	rm test *.png
