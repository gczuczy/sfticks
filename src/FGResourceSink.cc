
#include "FGResourceSink.hh"

FGResourceSink::FGResourceSink(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::ResourceSink, _reader, _fgoh), c_mProducingTimer(0) {
  setObjDefDecls({"mCouponInventory"});

  defineProperty("mProducingTimer", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mProducingTimer);});
}

FGResourceSink::~FGResourceSink() {
}

