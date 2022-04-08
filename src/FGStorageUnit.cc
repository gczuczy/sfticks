
#include "FGStorageUnit.hh"
#include "ObjectProperty.hh"
#include "ArrayProperty.hh"
#include "StructProperty.hh"
#include "IntProperty.hh"

FGStorageUnit::StorageInventory::StorageInventory(Reader& _reader, FGObjectHeader& _fgoh)
  : FGComponent(FGComponentType::StorageInventory, _reader, _fgoh) {
  defineProperty(std::make_shared<ArrayProperty<StructProperty<InventoryStack> > >("mInventoryStacks", c_mInventoryStacks));
  defineProperty(std::make_shared<ArrayProperty<IntProperty> >("mArbitrarySlotSizes", c_mArbitrarySlotSizes));
  defineProperty(std::make_shared<ArrayProperty<ObjectProperty> >("mAllowedItemDescriptors", c_mAllowedItemDescriptors));
}

FGComponentSP FGStorageUnit::StorageInventory::instantiate(Reader& _reader, FGObjectHeader& _fgoh) {
  return std::make_shared<FGStorageUnit::StorageInventory>(_reader, _fgoh);
}

FGStorageUnit::FGStorageUnit(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh, int32_t _capacity)
  : FGBuilding(_et, _reader, _fgoh), c_capacity(_capacity) {
  defineProperty(std::make_shared<ObjectProperty>("mStorageInventory", c_mStorageInventory));
}

FGStorageUnit::~FGStorageUnit() {
}

