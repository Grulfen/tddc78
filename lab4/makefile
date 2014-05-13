CC=icc

EXE = lab4
BIN=bin

CFLAGS = -g -Nmpi -std=c99
LFLAGS = -lm -Nmpi

all: $(EXE)

lab4: $(BIN)/lab4.o $(BIN)/physics.o
	$(CC) $^ $(LFLAGS) -o $@

$(BIN)/%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
