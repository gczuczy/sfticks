
#ifndef SFT_FGFACTORYCONNECTIONCOMPONENT_H
#define SFT_FGFACTORYCONNECTIONCOMPONENT_H

#include "FGComponent.hh"
#include "FGEnums.hh"
//#include "InventoryStack.hh"
#include "ObjectReference.hh"
#include "FGInventoryComponent.hh"

#include <vector>
#include <set>

namespace FG {

  class FactoryConnectionComponent: public Component {
  public:
    FactoryConnectionComponent() = delete;
    FactoryConnectionComponent(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~FactoryConnectionComponent()=default;
    static ComponentSP instantiate(Reader& _reader, ObjectHeader& _fgoh);

    virtual std::string vtypename();

    inline InventoryComponentSP connectionInventory() {
      return c_mConnectionInventory.as<InventoryComponent>();
    };
    inline int32_t inventoryAccessIndex() const {return c_mInventoryAccessIndex;};
    inline EFactoryConnectionDirection direction() const {return c_mDirection;};
    inline ComponentSP connectedComponent() {return c_mConnectedComponent.as<Component>();};
    virtual std::string compdetails();

  public:
    static std::set<std::string> pathname;
    static ComponentType componenttype;

  private:
    ObjectReference c_mConnectedComponent, c_mConnectionInventory;
    int32_t c_mInventoryAccessIndex=0;
    EFactoryConnectionDirection c_mDirection;
  };
  typedef std::shared_ptr<FactoryConnectionComponent> FactoryConnectionComponentSP;

#if 0
  // and alias it
  class FGFactoryConnectionComponent: public FactoryConnectionComponent {
  public:
    FGFactoryConnectionComponent() = delete;
    FGFactoryConnectionComponent(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~FGFactoryConnectionComponent()=default;
    virtual std::string vtypename();
    static std::string pathname;
  };
#endif

}

#endif
