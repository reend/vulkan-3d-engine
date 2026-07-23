CFLAGS = -std=c++17 -O2 -I.
LDFLAGS = $(shell pkg-config --libs glfw3 vulkan)
GLSLC = glslc

vertSources = $(shell find ./shaders -type f -name "*.vert")
vertObjFiles = $(patsubst %.vert, %.vert.spv, $(vertSources))
fragSources = $(shell find ./shaders -type f -name "*.frag")
fragObjFiles = $(patsubst %.frag, %.frag.spv, $(fragSources))

TARGET = a.out

.PHONY: run test clean

run: $(TARGET)
	./$(TARGET)

test: run

$(TARGET): $(vertObjFiles) $(fragObjFiles) *.cpp *.hpp
	g++ $(CFLAGS) -o $(TARGET) *.cpp $(LDFLAGS)

%.spv: %
	$(GLSLC) $< -o $@

clean:
	rm -f $(TARGET)
	rm -f $(vertObjFiles) $(fragObjFiles)
