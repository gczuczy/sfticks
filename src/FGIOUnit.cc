
#include "FGIOUnit.hh"

FGIOUnit::FGIOUnit(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh)
  : FGBuilding(_et, _reader, _fgoh) {
}

FGIOUnit::FGIOUnit(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh, const std::set<std::string>& _objdefdecls)
  : FGBuilding(_et, _reader, _fgoh, std::move(_objdefdecls)) {
}

FGIOUnit::~FGIOUnit() {
}

