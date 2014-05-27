CC=icpc

EXE=lab4 rapport
BIN=bin

CFLAGS = -g -Nmpi -Wextra -Wall -W -pedantic -std=c++0x
LFLAGS = -lm -Nmpi

all: $(EXE)

lab4: $(BIN)/lab4.o $(BIN)/physics.o
	$(CC) $^ $(LFLAGS) -o $@

$(BIN)/%.o: %.cc
	$(CC) $(CFLAGS) -c $^ -o $@

rapport: lab4.tex
	pdflatex lab4.tex
	pdflatex lab4.tex
	pdflatex lab4.tex

clean:
	rm -f $(BIN)/*.o $(EXE)
	rm -f lab4.aux lab4.log lab4.toc
