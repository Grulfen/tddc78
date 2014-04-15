#!/usr/bin/env python3

import sys
import re

if len(sys.argv) != 2:
    print("Usage: get_average_time.py infile")

infile = sys.argv[1]

line = ""
image = 0
times = {}
tmp_list = []
time = 0

with open(infile, 'r') as ifile:
    line = ifile.readline()
    while(line):
        if line.startswith("Image"):
            image = int(line[6])
        elif line.startswith("Filtering"):
            time = float(re.search("\d+.\d+", line).group())
            tmp_list = times.get(image, [])
            tmp_list.append(time)
            times[image] = tmp_list
        line = ifile.readline()

aver_times = {}
for key in times:
    aver_times[key] = sum(times[key][1:])/(len(times[key])-1)


for key in aver_times:
    print("Image {0}: Average time {1:.7f}\n".format(key, aver_times[key]))
