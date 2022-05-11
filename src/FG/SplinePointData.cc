
#include "FG/SplinePointData.hh"

#include "misc.hh"

namespace FG {

  std::string SplinePointData::str() const {
    return strprintf("Location:%s ArriveTangent:%s LeaveTangent:%s",
		     Location.str().c_str(),
		     ArriveTangent.str().c_str(),
		     LeaveTangent.str().c_str());
  }

}
