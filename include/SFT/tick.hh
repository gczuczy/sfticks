
#ifndef SFT_TICK_H
#define SFT_TICK_H

#include <stdint.h>

namespace SFT {

  struct tickinfo_t {
    int64_t tickno;
    float timedelta; // seconds since last tick
  };

}

#endif
