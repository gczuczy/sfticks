
#ifndef SFT_TRANSFORM_H
#define SFT_TRANSFORM_H

#include "vectors.hh"
#include <string>

namespace FG {

  struct Transform {
    Quat Rotation;
    Vector3 Translation;
    inline std::string str() {return "";};
  };
}

#endif
