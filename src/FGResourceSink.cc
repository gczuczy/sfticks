
#include "FGResourceSink.hh"
#include "ObjectProperty.hh"
#include "FloatProperty.hh"

FGResourceSink::FGResourceSink(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::ResourceSink, _reader, _fgoh), c_mProducingTimer(0) {
  defineProperty(std::make_shared<ObjectProperty>("mCouponInventory", c_mCouponInventory));
  defineProperty(std::make_shared<FloatProperty>("mProducingTimer", c_mProducingTimer));
}

FGResourceSink::~FGResourceSink() {
}

