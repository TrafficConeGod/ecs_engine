OBJECTS = $(patsubst %.cc,%.o, $(shell find ./src/ ./lib/ -name *.cc))
CC = g++
CFLAGS = -c -I src -I lib -Wall -std=c++17 -O2 -finline-functions -fPIC

LDFLAGS = -pthread -lGL -lglut -lGLEW -lglfw -lm -lX11 -lpthread -lXi -lXrandr -ldl

OUT_FILE = libnewt.so

.PHONY: build
build: $(OBJECTS)
	$(CC) -shared -o $(OUT_FILE) $(OBJECTS) $(LDFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OBJECTS) $(OUT_FILE)
