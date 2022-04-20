
#include "FGConveyorBelt.hh"
#include "ArrayProperty.hh"
#include "StructProperty.hh"
#include "ObjectProperty.hh"
#include "Trace.hh"

namespace FG {

  ConveyorBelt::ConveyorBelt(EntityType _et, Reader& _reader, ObjectHeader& _fgoh, int32_t _throughput)
    : Building(_et, _reader, _fgoh), c_throughput(_throughput) {
    defineProperty(std::make_shared<ArrayProperty<StructProperty<SplinePointData> > >("mSplineData", c_mSplineData));

    // components
    registerComponent("ConveyorAny0", c_ConveyorAny0);
    registerComponent("ConveyorAny1", c_ConveyorAny1);

    // supplemental data handler
    defineSupplementalHandler(std::bind(&ConveyorBelt::supplementalHandler,
					this,
					std::placeholders::_1));
  }

  ConveyorBelt::~ConveyorBelt() {
  }

  void ConveyorBelt::supplementalHandler(Reader& _reader) {
    TRACE;
    int32_t count;
    std::string unused;

    _reader.skip(4);
    _reader(count);
    printf("sup cnt: %i\n", count);

    for (int i=0; i<count; ++i) {
      BeltItem bi;
      _reader.skip(4);
      _reader(bi.item.pathName())(bi.item.levelName())(unused)(bi.position);
      c_belt_items.push_back(bi);
    }
  }
}
