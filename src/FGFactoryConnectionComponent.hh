
#ifndef SFT_FGFACTORYCONNECTIONCOMPONENT_H
#define SFT_FGFACTORYCONNECTIONCOMPONENT_H

#include "FGComponent.hh"
#include "FGEnums.hh"
//#include "InventoryStack.hh"
#include "ObjectReference.hh"

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

    inline ObjectReference& mConnectedComponent() {return c_mConnectedComponent;};
    inline ObjectReference& mConnectionInventory() {return c_mConnectionInventory;};
    inline int32_t mInventoryAccessIndex() const {return c_mInventoryAccessIndex;};
    inline EFactoryConnectionDirection mDirection() const {return c_mDirection;};
    inline ObjectReference mConnectedComponent() const {return c_mConnectedComponent;};
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
