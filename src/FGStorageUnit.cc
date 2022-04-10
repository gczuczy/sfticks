
#include "FGStorageUnit.hh"
#include "ObjectProperty.hh"

namespace FG {

  StorageUnit::StorageUnit(EntityType _et, Reader& _reader, ObjectHeader& _fgoh, int32_t _capacity)
    : Building(_et, _reader, _fgoh), c_capacity(_capacity) {
    defineProperty(std::make_shared<ObjectProperty>("mStorageInventory", c_mStorageInventory));

    defineInventories({"StorageInventory"});
  }

  StorageUnit::~StorageUnit() {
  }

}
