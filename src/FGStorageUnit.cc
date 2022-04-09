
#include "FGStorageUnit.hh"
#include "ObjectProperty.hh"

FGStorageUnit::FGStorageUnit(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh, int32_t _capacity)
  : FGBuilding(_et, _reader, _fgoh), c_capacity(_capacity) {
  defineProperty(std::make_shared<ObjectProperty>("mStorageInventory", c_mStorageInventory));
}

FGStorageUnit::~FGStorageUnit() {
}

