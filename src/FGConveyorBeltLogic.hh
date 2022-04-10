
#ifndef SFT_FGCONVEYORBELTLOGIC_H
#define SFT_FGCONVEYORBELTLOGIC_H

#include "FGBuilding.hh"
#include "ObjectReference.hh"
#include "FGFactoryConnectionComponent.hh"
#include "FGInventoryComponent.hh"

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

  private:
    //virtual void deserialize(Reader &_reader);
    ObjectReference c_mBufferInventory;
  };

  typedef std::shared_ptr<ConveyorBeltLogic> ConveyorBeltLogicSP;

}

#endif
