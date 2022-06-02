
#ifndef SFT_FGCONVEYORBELTLOGIC_H
#define SFT_FGCONVEYORBELTLOGIC_H

#include "FG/Building.hh"
#include "FG/ObjectReference.hh"
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

    virtual void associateComponents();
    virtual bool recv(DescObjectSP& _item, SFT::tickinfo_t& _tick, FactoryConnectionComponent& _src);

  protected:
    inline InventoryComponentSP& bufferInventory() {return c_bufferinventory;};

  private:
    ObjectReference c_mBufferInventory;
    InventoryComponentSP c_bufferinventory=nullptr;
  };

  typedef std::shared_ptr<ConveyorBeltLogic> ConveyorBeltLogicSP;

}

#endif
