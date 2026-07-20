CFLAGS = -std=c++17 -O2 -I.
LDFLAGS = $(shell pkg-config --libs glfw3 vulkan)

a.out: *.cpp *.hpp
	g++ $(CFLAGS) -o a.out *.cpp $(LDFLAGS)

.PHONY: test clean

test: a.out
	./a.out

clean:
	rm -f a.out
