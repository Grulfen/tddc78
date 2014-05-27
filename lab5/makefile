CC=icpc

EXE=lab5
BIN=bin

CFLAGS = -g -Nmpi -Wextra -Wall -W -pedantic -std=c++0x
LFLAGS = -lm -Nmpi

CFLAGS  += -tcollect -I$(VT_ROOT)/include
LFLAGS  += -L$(VT_LIB_DIR) -lVT $(VT_ADD_LIBS)

all: $(EXE)

lab5: $(BIN)/lab5.o $(BIN)/physics.o
	$(CC) $^ $(LFLAGS) -o $@

$(BIN)/%.o: %.cc
	$(CC) $(CFLAGS) -c $^ -o $@

rapport: lab5.tex
	pdflatex lab5.tex
	pdflatex lab5.tex
	pdflatex lab5.tex

clean:
	rm -f $(BIN)/*.o $(EXE)
	rm -f lab5.aux lab5.log lab5.toc
