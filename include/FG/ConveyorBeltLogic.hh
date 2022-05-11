
#ifndef SFT_FGCONVEYORBELTLOGIC_H
#define SFT_FGCONVEYORBELTLOGIC_H

#include "FG/Building.hh"
#include "FG/ObjectReference.hh"
#include "FG/FactoryConnectionComponent.hh"
#include "FG/InventoryComponent.hh"

#include <vector>

namespace FG {

  // this is an abstraction class for mergers/splitters and alike

  // this will need some generic interface for querying the
  // inputs and outputs
  class ConveyorBeltLogic: public Building {
  public:
    ConveyorBeltLogic()=delete;
    ConveyorBeltLogic(EntityType _et, Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ConveyorBeltLogic();

    inline ObjectReference& bufferInventory() {return c_mBufferInventory;};

  private:
    //virtual void deserialize(Reader &_reader);
    ObjectReference c_mBufferInventory;
  };

  typedef std::shared_ptr<ConveyorBeltLogic> ConveyorBeltLogicSP;

}

#endif
