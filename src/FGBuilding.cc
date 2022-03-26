
#include "FGBuilding.hh"

FGBuilding::FGBuilding(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh)
  : FGEntity(_et, _reader, _fgoh) {
}

FGBuilding::FGBuilding(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh, const std::set<std::string>& _objdefdecls)
  : FGEntity(_et, _reader, _fgoh, std::move(_objdefdecls)) {
}

FGBuilding::~FGBuilding() {
}
