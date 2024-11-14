#include "perf_timer.hpp"

#include <chrono>
#include <cstdint>
#include <fstream>

static const std::string log_prefix = "|   ";

void Timer::start_timing(std::string comment)
{
    uint64_t cur_time_ns = std::chrono::system_clock::now().time_since_epoch().count();
    active_timers.push(cur_time_ns);
    for (int i = 0; i < active_timers.size() - 1; ++i) {
        log_output.append(log_prefix);
    }
    log_output.append("STARTTIMING: " + comment + "\n");
}

void Timer::stop_timing(std::string comment)
{
    uint64_t end_time_ns = std::chrono::system_clock::now().time_since_epoch().count();
    uint64_t start_time_ns = active_timers.top();
    active_timers.pop();
    uint64_t timing_duration_ns = end_time_ns - start_time_ns;
    for (int i = 0; i < active_timers.size(); ++i) {
        log_output.append(log_prefix);
    }
    uint32_t duration_ms = timing_duration_ns / 1'000'000;
    log_output.append("STOPTIMING: " + comment + " " + std::to_string(duration_ms) + "ms\n");
}

void Timer::comment(std::string comment)
{
    if (active_timers.size() > 0) {
        for (int i = 0; i < active_timers.size() - 1; ++i) {
            log_output.append(log_prefix);
        }
    }
    log_output.append("COMMENT: " + comment + "\n");
}

int Timer::dump(std::string filename)
{
    std::ofstream log_file;
    log_file.open(filename);
    log_file << log_output;
    log_file.close();
    return 0;
}
