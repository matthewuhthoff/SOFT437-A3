import statistics
import matplotlib.pyplot as plt


def main():
    write_times = []
    file = open('build/stop_write_overhead.txt', 'r')
    for line in file:
        write_times.append(int(line))
    plt.plot(write_times)
    plt.savefig("stop_write_overhead.png")
    print(statistics.mean(write_times))


if __name__ == '__main__':
    main()
