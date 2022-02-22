
#ifndef SFT_TIMER_H
#define SFT_TIMER_H

#include <sys/time.h>

#include <string>

class Timer {
public:
  Timer() = delete;
  Timer(const Timer&) = delete;
  Timer(const std::string _name, bool _freq=false);
  ~Timer();

private:
  std::string c_name;
  bool c_freq;
  struct timeval c_start;
};

#endif
