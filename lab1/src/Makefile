CC=icc

CFLAGS = -Nmpi -g

LFLAGS= -lpthread -lrt -lm -Nmpi

all: blurc thresc

clean:
	-$(RM) *.o blurc thresc

blurc: ppmio.o gaussw.o blurfilter.o blurmain.o
	$(CC) -o $@ ppmio.o gaussw.o blurfilter.o blurmain.o $(CFLAGS) $(LFLAGS)

thresc: thresmain.o ppmio.o thresfilter.o
	$(CC) -o  $@ thresmain.o ppmio.o thresfilter.o $(CFLAGS) $(LFLAGS)

arc:
	tar cf - *.c *.h *.f90 Makefile Makefile.sgi|gzip - > filters.tar.gz
