CC=gfortran
EXE= lab3\
     orig

FLAGS= -fopenmp

all: $(EXE)

lab3: laplsolv.f90
	$(CC) $(FLAGS) -o $@ $^

nomp: laplsolv.f90
	$(CC) -o $@ $^

orig: laplsolv_orig.f90
	$(CC) -o $@ $^

clean:
	rm -f $(EXE)
