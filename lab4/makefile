CC=icc

EXE = lab4
BIN=bin

CFLAGS = -g -Nmpi -std=c99
LFLAGS = -lm -Nmpi

all: $(EXE)

lab4: physics.o
	$(CC) $^ -o $@

$(BIN)/%.o: %.c
	$(CC) -c $^ -o $@
