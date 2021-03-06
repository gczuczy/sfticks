
#ifndef SFT_FGSTORAGEUNIT_H
#define SFT_FGSTORAGEUNIT_H

#include "FG/Building.hh"
#include "FG/ObjectReference.hh"

#include "FG/InventoryComponent.hh"

namespace FG {

  /*
    This is a base class for Input/Output units.
    An input-output unit is everything that has at least input or output, and
    does something with it, apart from storing it.
  */
  class StorageUnit: public Building {
  public:
    StorageUnit()=delete;
    StorageUnit(EntityType _et, Reader& _reader, ObjectHeader& _fgoh, int32_t _capacity);
    virtual ~StorageUnit();

    inline int32_t capacity() const {return c_capacity;};
    inline ObjectReference& storageInventory() {return c_mStorageInventory;};

    virtual void doTick(SFT::tickinfo_t& _tick);

  private:
    int32_t c_capacity;
    //virtual void deserialize(Reader &_reader);
    ObjectReference c_mStorageInventory;
  };

  typedef std::shared_ptr<StorageUnit> StorageUnitSP;

}

#endif
