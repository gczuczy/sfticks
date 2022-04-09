
#include "Timer.hh"

#include <sys/time.h>
#include <stdint.h>

namespace SFT {

  Timer::Timer(const std::string _name, bool _freq): c_name(_name), c_freq(_freq) {
    gettimeofday(&c_start, 0);
  }

  Timer::~Timer() {
    struct timeval end;
    gettimeofday(&end, 0);

    uint64_t diff;
    diff = (end.tv_sec - c_start.tv_sec)*1000000
      + end.tv_usec - c_start.tv_usec;

    if ( c_freq ) {
      printf("Timer(%s): %lu usec (freq: %lu ops/sec)\n", c_name.c_str(), diff, 1000000/diff);
    } else {
      printf("Timer(%s): %lu usec\n", c_name.c_str(), diff);
    }
  }

}
