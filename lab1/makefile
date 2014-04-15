
DATAFILE= result/thres/batch_thres_1.txt\
	  result/thres/batch_thres_2.txt\
	  result/thres/batch_thres_3.txt\
	  result/thres/batch_thres_4.txt\
	  result/thres/batch_thres_5.txt\
	  result/thres/batch_thres_6.txt\
	  result/thres/batch_thres_7.txt\
	  result/thres/batch_thres_8.txt\
	  result/thres/batch_thres_9.txt\
	  result/thres/batch_thres_10.txt\
	  result/thres/batch_thres_11.txt\
	  result/thres/batch_thres_12.txt\
	  result/thres/batch_thres_13.txt\
	  result/thres/batch_thres_14.txt\
	  result/thres/batch_thres_15.txt\
	  result/thres/batch_thres_16.txt

rapport: lab1.tex
	pdflatex lab1.tex
	pdflatex lab1.tex
	pdflatex lab1.tex

data: get_average_thresh.py $(DATAFILE)
	python3 get_average_thresh.py > result/thres/result.txt

plot: data thresh.p
	python3 gen_thres_dat.py
	gnuplot thresh.p

clean:
	rm -f lab1.aux lab1.log lab1.toc

cleanall:
	rm -f lab1.pdf result/thres/result.txt result/thres/result.dat threshold.png
