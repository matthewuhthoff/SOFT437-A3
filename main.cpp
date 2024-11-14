#include "perf_timer.hpp"

#include <chrono>
#include <random>
#include <thread>
#include <vector>

void bubble_sort(std::vector<int>& arr)
{
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

int partition(std::vector<int>& arr, int start, int end)
{
    int pivot = arr.at(end);

    int i = start - 1;

    for (int j = start; j <= end - 1; ++j) {
        if (arr.at(j) < pivot) {
            ++i;
            std::swap(arr.at(i), arr.at(j));
        }
    }

    std::swap(arr.at(i + 1), arr[end]);
    return i + 1;
}

void quick_sort(std::vector<int>& arr, int start, int end)
{
    if (start < end) {
        int pi = partition(arr, start, end);
        quick_sort(arr, start, pi - 1);
        quick_sort(arr, pi + 1, end);
    }
}

std::vector<int> populate_array(int num, int low, int high)
{
    std::vector<int> arr;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(low, high);
    for (int i = 0; i < num; ++i) {
        arr.push_back(dist(rng));
    }
    return arr;
}

Timer* Timer::timer_instance;

int main()
{
    Timer* timer = Timer::activate(true);

    std::vector<int> array = populate_array(10'000, 1, 99999);
    std::vector<int> array_2 = array;
    int start = 0;
    int end = array.size();

    timer->start_timing("Start Quick Sort");
    quick_sort(array, start, end - 1);
    timer->stop_timing("End Quick Sort");

    timer->start_timing("Start Bubble Sort");
    bubble_sort(array_2);
    timer->stop_timing("End Bubble Sort");

    timer->dump("logs.txt");

    return 0;
}
