
#include "FGResourceSink.hh"
#include "ObjectProperty.hh"
#include "FloatProperty.hh"

namespace FG {

  std::string ResourceSink::objtypename("Build_ResourceSink_C");

  ResourceSink::ResourceSink(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::ResourceSink, _reader, _fgoh), c_mProducingTimer(0) {
    defineProperty(std::make_shared<ObjectProperty>("mCouponInventory", c_mCouponInventory));
    defineProperty(std::make_shared<FloatProperty>("mProducingTimer", c_mProducingTimer));
  }

  ResourceSink::~ResourceSink() {
  }

}
