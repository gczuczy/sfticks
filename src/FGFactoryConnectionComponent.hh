
#ifndef SFT_FGFACTORYCONNECTIONCOMPONENT_H
#define SFT_FGFACTORYCONNECTIONCOMPONENT_H

#include "FGComponent.hh"
#include "FGEnums.hh"
//#include "InventoryStack.hh"
#include "ObjectReference.hh"

#include <vector>

namespace FG {

  class FactoryConnectionComponent: public Component {
  public:
    FactoryConnectionComponent() = delete;
    FactoryConnectionComponent(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~FactoryConnectionComponent()=default;
    static ComponentSP instantiate(Reader& _reader, ObjectHeader& _fgoh);

    inline ObjectReference& mConnectedComponent() {return c_mConnectedComponent;};
    inline ObjectReference& mConnectionInventory() {return c_mConnectionInventory;};
    inline int32_t mInventoryAccessIndex() const {return c_mInventoryAccessIndex;};
    inline EFactoryConnectionDirection mDirection() const {return c_mDirection;};
    inline ObjectReference mConnectedComponent() const {return c_mConnectedComponent;};

  public:
    static std::string pathname;

  private:
    ObjectReference c_mConnectedComponent, c_mConnectionInventory;
    int32_t c_mInventoryAccessIndex;
    EFactoryConnectionDirection c_mDirection;
  };

}

#endif
