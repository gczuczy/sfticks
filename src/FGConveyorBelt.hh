
#ifndef SFT_FGCONVEYORBELT_H
#define SFT_FGCONVEYORBELT_H

#include "FGBuilding.hh"
#include "SplinePointData.hh"
#include "FGFactoryConnectionComponent.hh"

#include <vector>

namespace FG {

  class ConveyorBelt: public Building {
  public:
    ConveyorBelt()=delete;
    ConveyorBelt(EntityType _et, Reader& _reader, ObjectHeader& _fgoh, int32_t _throughput);
    virtual ~ConveyorBelt();

    inline int32_t throughput() const {return c_throughput;};
    inline std::vector<SplinePointData>& splineData() {return c_mSplineData;};
    inline FactoryConnectionComponentSP ConveyorAny0() {return c_ConveyorAny0;};
    inline FactoryConnectionComponentSP ConveyorAny1() {return c_ConveyorAny1;};

  private:
    int32_t c_throughput; // items per minute
    std::vector<SplinePointData> c_mSplineData;
    FactoryConnectionComponentSP c_ConveyorAny0, c_ConveyorAny1;
  };

  typedef std::shared_ptr<ConveyorBelt> ConveyorBeltSP;

}

#endif
