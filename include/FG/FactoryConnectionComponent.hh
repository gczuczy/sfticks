
#ifndef SFT_FGFACTORYCONNECTIONCOMPONENT_H
#define SFT_FGFACTORYCONNECTIONCOMPONENT_H

#include "FG/Component.hh"
#include "FG/Enums.hh"
//#include "InventoryStack.hh"
#include "FG/ObjectReference.hh"
#include "FG/InventoryComponent.hh"
#include "SFT/tick.hh"

#include <vector>
#include <set>

namespace FG {

  class Building;
  class FactoryConnectionComponent: public Component {
  public:
    FactoryConnectionComponent() = delete;
    FactoryConnectionComponent(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~FactoryConnectionComponent()=default;
    static ComponentSP instantiate(Reader& _reader, ObjectHeader& _fgoh);
    void setIndex(uint32_t _index);

    virtual std::string vtypename();

    inline InventoryComponentSP connectionInventory() {
      return c_mConnectionInventory.as<InventoryComponent>();
    };
    inline int32_t inventoryAccessIndex() const {return c_mInventoryAccessIndex;};
    inline EFactoryConnectionDirection direction() const {return c_mDirection;};
    inline std::shared_ptr<FactoryConnectionComponent> connectedComponent() {return c_connectedcomponent;};
    inline bool isConnected() const {return (bool)c_connectedcomponent;};
    inline InventoryComponentSP inventory() {return c_connectioninventory;};
    inline uint32_t index() const {return c_index;};

    virtual std::string compdetails();
    virtual std::string str();
    virtual void finalize();

    // sending and recieving
    // send is now called by $Entity::doTicks
    // and recv is called by send
    bool send(DescObjectSP& _item, SFT::tickinfo_t& _tick);
  protected:
    bool recv(DescObjectSP& _item, SFT::tickinfo_t& _tick);

  public:
    static std::set<std::string> pathname;
    static ComponentType componenttype;

  private:
    ObjectReference c_mConnectedComponent, c_mConnectionInventory;
    std::shared_ptr<FactoryConnectionComponent> c_connectedcomponent;
    InventoryComponentSP c_connectioninventory=nullptr;
    int32_t c_mInventoryAccessIndex=0;
    EFactoryConnectionDirection c_mDirection = EFactoryConnectionDirection::FCD_ANY;
    std::shared_ptr<Building> c_building=nullptr;
    uint32_t c_index=0;
  };
  typedef std::shared_ptr<FactoryConnectionComponent> FactoryConnectionComponentSP;

}

#endif
