#include <cstdint>
#include <stdio.h>
#include <string>
#include <stack>
#include <chrono>
#include <ctime>

class Timer
{
  private:
      static Timer* timer_instance;
      Timer() {}

      std::stack<uint64_t> active_timers;
      std::string log_output;

  public:
    Timer(const Timer& obj) = delete; // no copy constructor
    static Timer* activate(bool onoff) {
        if (!onoff) {
            return nullptr;
        }
        if (timer_instance == nullptr) {
            timer_instance = new Timer();
        }
        return timer_instance;
    }

    void start_timing(std::string comment);
    void stop_timing(std::string comment);
    void comment(std::string comment);
    int dump(std::string filename);
};
