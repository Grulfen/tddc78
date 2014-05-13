rapport: lab2.tex
	pdflatex lab2.tex
	pdflatex lab2.tex
	pdflatex lab2.tex

data: get_average_thresh.py get_average_blur.py
	python3 get_average_thresh.py > result/threshold/result.txt
	python3 get_average_blur.py > result/blur/result.txt

plot: data thresh.p 
	python3 gen_thres_dat.py
	python3 gen_blur_dat.py
	gnuplot thresh.p
	gnuplot blur.p

clean:
	rm -f lab2.aux lab2.log lab2.toc

cleanall:
	rm -f lab2.pdf result/threshold/result.txt result/threshold/result.dat threshold.png blur_4.png blur_8.png blur_16.png blur_32.png result/blur/result.txt result/blur/blur_4.dat result/blur/blur_8.dat result/blur/blur_16.dat result/blur/blur_32.dat
