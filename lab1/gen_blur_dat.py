import re

def print_first(radius):
    with open("result/blur/result_{0}.dat".format(radius), 'w') as ofile:
        ofile.write("#processes\t1\t\t2\t\t3\t\t4\n")

def print_times(process, times, radius):
    with open("result/blur/result_{0}.dat".format(radius), 'a') as ofile:
        ofile.write("{0}\t".format(process))
        ofile.write("\t".join(times))
        ofile.write("\n")

line = ""
process = 0
image = 0
times = {}
for i in [4,8,16,32]:
    print_first(i)

with open("result/blur/result.txt", 'r') as ifile:
    line = True
    while line:
        line = ifile.readline()
        tmp_line = line.split()
        if not tmp_line:
            continue
        start = tmp_line[0]
        if start.isdigit():
            process = int(start)
            times = {}
        if start == "Image":
            image = int(re.search("\d+", line).group())
        elif start == "Radius":
            radius = int(re.search("\d+", line).group())
            time = re.search("\d+.\d+", line).group()
            tmp_times = times.get(radius, [])
            tmp_times.append(time)
            times[radius] = tmp_times
            if radius == 32 and image == 4:
                for r in sorted(times.keys()):
                    print_times(process, times[r], r)
