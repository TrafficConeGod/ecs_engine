OBJECTS = $(patsubst %.cc,%.o, $(shell find ./ -name *.cc))
CC = g++
CFLAGS = -c -I ../../src -I ../../lib -I . -Wall -std=c++17 -O2 -finline-functions -g

LDFLAGS = -L../../ -pthread -lnewt -lfmt -Wl,-rpath='$$ORIGIN/../../'

OUT_FILE = app.elf

.PHONY: build
build: $(OBJECTS)
	$(CC) -o $(OUT_FILE) $(OBJECTS) $(LDFLAGS)

run: build
	./$(OUT_FILE)

pipe_run: build
	./$(OUT_FILE) > debug.out

%.o: %.cc
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OBJECTS) $(OUT_FILE)
