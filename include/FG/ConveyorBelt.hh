
#ifndef SFT_FGCONVEYORBELT_H
#define SFT_FGCONVEYORBELT_H

#include "FG/Building.hh"
#include "FG/SplinePointData.hh"
#include "FG/FactoryConnectionComponent.hh"

#include <vector>
#include <list>

namespace FG {

  class ConveyorBelt: public Building {\
  public:
    struct BeltItem {
      float position=0;
      ObjectReference item;
    };
    typedef std::list<BeltItem> BeltItems;
  public:
    ConveyorBelt()=delete;
    ConveyorBelt(EntityType _et, Reader& _reader, ObjectHeader& _fgoh, int32_t _throughput);
    virtual ~ConveyorBelt();

    inline int32_t throughput() const {return c_throughput;};
    inline std::vector<SplinePointData>& splineData() {return c_mSplineData;};
    inline FactoryConnectionComponentSP ConveyorAny0() {return c_ConveyorAny0;};
    inline FactoryConnectionComponentSP ConveyorAny1() {return c_ConveyorAny1;};
    inline BeltItems& beltItems() {return c_belt_items;};

    virtual float length();

  private:
    void supplementalHandler(Reader& _r);

  private:
    int32_t c_throughput; // items per minute
    std::vector<SplinePointData> c_mSplineData;
    FactoryConnectionComponentSP c_ConveyorAny0, c_ConveyorAny1;
    BeltItems c_belt_items;
  };

  typedef std::shared_ptr<ConveyorBelt> ConveyorBeltSP;

}

#endif
