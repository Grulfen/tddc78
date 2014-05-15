CC=icpc

EXE=lab4
BIN=bin

CFLAGS = -g -Nmpi -Wextra -Wall -W -pedantic -std=c++0x
LFLAGS = -lm -Nmpi

all: $(EXE)

lab4: $(BIN)/lab4.o $(BIN)/physics.o
	$(CC) $^ $(LFLAGS) -o $@

$(BIN)/%.o: %.cc
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(BIN)/*.o $(EXE)
