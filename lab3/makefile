all: rapport

plot:
	gnuplot omp.p	

rapport: plot lab3.tex
	pdflatex lab3.tex
	pdflatex lab3.tex
	pdflatex lab3.tex

clean:
	rm -f lab3.aux lab3.log lab3.toc omp.png

cleanall: clean
	rm -f lab3.pdf

