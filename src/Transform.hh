
#ifndef SFT_TRANSFORM_H
#define SFT_TRANSFORM_H

#include "vectors.hh"

namespace FG {

  struct Transform {
    Quat Rotation;
    Vector3 Translation;
  };
}

#endif
