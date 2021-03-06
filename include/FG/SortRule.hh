
#ifndef SFT_SORTRULE_HH
#define SFT_SORTRULE_HH

#include <string>
#include <stdint.h>

#include "FG/ObjectReference.hh"

namespace FG {

  struct SplitterSortRule {
    SplitterSortRule()=default;
    ~SplitterSortRule()=default;
    ObjectReference ItemClass;
    int32_t OutputIndex;
    std::string str();
  };

}

#endif
