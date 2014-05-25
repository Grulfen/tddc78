#!/usr/bin/env python3
import re

def print_first():
    with open("result.dat", 'w') as ofile:
        ofile.write("#threads\t\ttime\n")


def print_times(thread, time):
    with open("result.dat", 'a') as ofile:
        ofile.write("{0}\t\t".format(thread))
        ofile.write(str(time))
        ofile.write("\n")

line = ""
thread = 0
thread_old = 0
times = []
print_first()
with open("src/result.txt", 'r') as ifile:
    line = ifile.readline()
    while line:
        start = line.split()
        if not start:
            line = ifile.readline()
            continue
        start = start[0]
        if start.isdigit():
            thread_old = thread
            thread = int(start)
            if thread != 1:
                times.sort()
                print_times(thread_old, sum(times[:-1])/len(times[:-1]))
            times = []
        if start == "Time:":
            time = float(re.search("\d+.\d+", line).group())
            times.append(time)

        line = ifile.readline()
    print_times(thread, sum(times[:-1])/len(times[:-1]))
