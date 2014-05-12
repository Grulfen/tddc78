import re

def get_aver_times(infile):
    line = ""
    image = 0
    times = {}
    tmp_list = []
    time = 0

    try:
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
    except IOError:
        return None

    aver_times = {}
    for key in times:
        aver_times[key] = sum(times[key][1:])/(len(times[key])-1)

    return aver_times


def main():
    for i in range(1,20):
        aver_times = get_aver_times("result/threshold/times_{0}.txt".format(i))
        if aver_times is not None:
            print("{0} processes".format(i))
            for key in aver_times:
                print("Image {0}: Average time {1:.7f}".format(key, aver_times[key]))
            print()

if __name__ == '__main__':
    main()
