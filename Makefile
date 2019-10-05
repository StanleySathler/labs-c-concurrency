CC = gcc
CFLAGS = -lm

compile: src/main.o
	mkdir -p bin
	$(CC) -o bin/main.bin src/main.o $(CFLAGS)
	make clean

exec:
	./bin/main.bin

clean:
	rm src/*.o

.PHONY: clean compile exec
