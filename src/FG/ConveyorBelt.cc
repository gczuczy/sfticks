
#include "FG/ConveyorBelt.hh"
#include "FG/ArrayProperty.hh"
#include "FG/StructProperty.hh"
#include "FG/ObjectProperty.hh"
#include "SFT/Trace.hh"

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

  float ConveyorBelt::length() {
    float d(0);

    if ( c_mSplineData.size() < 2 )
      EXCEPTION("ConveyorBelt::length needs at least 2 points");

    Vector3 prev = c_mSplineData[0].Location;

    for (int i=1; i<c_mSplineData.size(); ++i) {
      d += (prev - c_mSplineData[i].Location).length();
      prev = c_mSplineData[i].Location;
    }

    return d;
  }

  void ConveyorBelt::supplementalHandler(Reader& _reader) {
    int32_t count;
    std::string unused;

    _reader.skip(4);
    _reader(count);

    std::string level,path;
    for (int i=0; i<count; ++i) {
      BeltItem bi;
      _reader.skip(4);
      _reader(path)(level)(unused)(bi.position);
      bi.item = std::move(ObjectReference(level, path));
      c_belt_items.push_back(bi);
    }
  }
}
