
#include "FGStorageUnit.hh"

FGStorageUnit::FGStorageUnit(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh, int32_t _capacity)
  : FGBuilding(_et, _reader, _fgoh), c_capacity(_capacity) {
  setObjDefDecls({"mStorageInventory"});
}

FGStorageUnit::~FGStorageUnit() {
}

