
#ifndef SFT_SPLINEPOINTDATA_H
#define SFT_SPLINEPOINTDATA_H

#include "vectors.hh"

namespace FG {

  struct SplinePointData {
    Vector3 Location;
    Vector3 ArriveTangent;
    Vector3 LeaveTangent;
    std::string str() const;
  };
}

#endif
