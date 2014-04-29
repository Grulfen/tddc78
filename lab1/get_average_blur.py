import re

def get_aver_times(infile):
    line = ""
    image = 0
    radius = 0
    times = {}
    tmp_list = []
    tmp_dir = {}
    time = 0

    try:
        with open(infile, 'r') as ifile:
            line = ifile.readline()
            while(line):
                if line.startswith("Image"):
                    image = int(re.findall("\d+", line)[0])
                    radius = int(re.findall("\d+", line)[-1])
                    times[image] = times.get(image, {})
                    times[image][radius] = []
                            
                elif line.startswith("Filtering"):
                    time = float(re.search("\d+.\d+", line).group())
                    times[image][radius] += [time]

                line = ifile.readline()
    except IOError:
        return None

    aver_times = {}
    for image_key, images_dict in sorted(times.items()):
        for radius_key, times_list in sorted(images_dict.items()):
            aver_times[image_key] = aver_times.get(image_key, {})
            aver_times[image_key][radius_key] = sum(times_list[1:])/(len(times_list)-1)
    return aver_times


def main():
    for i in range(1,49):
        aver_times = get_aver_times("result/blur/average_{0}.txt".format(i))
        if aver_times is not None:
            print("{0} processes".format(i))
            for image_key, images_dict in sorted(aver_times.items()):
                print("Image {0}".format(image_key))
                for radius_key, aver_time in sorted(images_dict.items()):
                    print("\tRadius {1}:\tAverage time:\t {2:.7f}".format(image_key,
                        radius_key, aver_time))
            print()

if __name__ == '__main__':
    main()
