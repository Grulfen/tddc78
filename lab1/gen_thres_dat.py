import sys
import re

def print_first():
    with open("result/thres/result.dat", 'w') as ofile:
        ofile.write("#processes\t1\t\t2\t\t3\t\t4\n")


def print_times(process, times):
    with open("result/thres/result.dat", 'a') as ofile:
        ofile.write("{0}\t".format(process))
        ofile.write("\t".join(times))
        ofile.write("\n")

line = ""
process = 0
times = []
print_first()
with open("result/thres/result.txt", 'r') as ifile:
    line = ifile.readline()
    while line:
        start = line.split(" ")[0]
        if start.isdigit():
            process = int(start)
            times = []
        if start == "Image":
            image = re.search("\d+", line).group()
            time = re.search("\d+.\d+", line).group()
            times.append(time)
            if int(image) == 4:
                print_times(process, times)
        line = ifile.readline()
