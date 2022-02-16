OBJECTS = $(patsubst %.cc,%.o, $(shell find ./src/ ./lib/ -name *.cc))
CC = g++
CFLAGS = -c -I src -I lib -Wall -std=c++17 -O2 -finline-functions -fPIC

LDFLAGS = -pthread -lGL -lglut -lGLEW -lglfw -lm -lX11 -lpthread -lXi -lXrandr -ldl

OUT_FILE = libnewt.so

.PHONY: build
build: $(OBJECTS)
	$(CC) -shared -o $(OUT_FILE) $(OBJECTS) $(LDFLAGS)

run: build
	./$(OUT_FILE)

pipe_run: build
	./$(OUT_FILE) > debug.out

%.o: %.cc
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OBJECTS) $(OUT_FILE)
