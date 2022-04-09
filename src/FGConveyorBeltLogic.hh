
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

    inline std::vector<FactoryConnectionComponentSP> inputs() {return c_inputs;};
    inline std::vector<FactoryConnectionComponentSP> outputs() {return c_outputs;};
    inline InventoryComponentSP StorageInventory() {return c_StorageInventory;};

  private:
    //virtual void deserialize(Reader &_reader);
    ObjectReference c_mBufferInventory;
    InventoryComponentSP c_StorageInventory;

  protected:
    std::vector<FactoryConnectionComponentSP> c_inputs, c_outputs;
  };

  typedef std::shared_ptr<ConveyorBeltLogic> ConveyorBeltLogicSP;

}

#endif
