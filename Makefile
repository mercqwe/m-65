CC = gcc
SRC = src/cpu.c src/opcodes.c src/main.c
BIN = bin/m65

all:
	mkdir -p bin
	$(CC) $(SRC) -o $(BIN)

clean:
	rm -f $(BIN)
