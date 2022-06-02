
#include "FG/FactoryConnectionComponent.hh"

#include "FG/ObjectProperty.hh"
#include "FG/EnumProperty.hh"
#include "FG/IntProperty.hh"
#include "SFT/Exception.hh"
#include "misc.hh"
#include "FG/Enums.hh"
#include "FG/Building.hh"

namespace FG {

  std::set<std::string> FactoryConnectionComponent::pathname{
    "/Script/FactoryGame.FactoryConnectionComponent",
      "/Script/FactoryGame.FGFactoryConnectionComponent",
      };
  ComponentType FactoryConnectionComponent::componenttype(ComponentType::FactoryConnection);

  FactoryConnectionComponent::FactoryConnectionComponent(Reader& _reader, ObjectHeader& _fgoh)
    : Component(ComponentType::FactoryConnection, _reader, _fgoh) {

    defineProperty(std::make_shared<ObjectProperty>("mConnectedComponent", c_mConnectedComponent));
    defineProperty(std::make_shared<ObjectProperty>("mConnectionInventory", c_mConnectionInventory));
    defineProperty(std::make_shared<EnumProperty<EFactoryConnectionDirection> >("mDirection", c_mDirection));
    defineProperty(std::make_shared<IntProperty>("mInventoryAccessIndex", c_mInventoryAccessIndex));
    //defineProperty(std::make_shared<ObjectProperty>("mConnectedComponent", c_mConnectedComponent));
  }

  ComponentSP FactoryConnectionComponent::instantiate(Reader& _reader, ObjectHeader& _fgoh) {
    return std::make_shared<FactoryConnectionComponent>(_reader, _fgoh);
  }

  void FactoryConnectionComponent::setIndex(uint32_t _index) {
    c_index = _index;
  }

  std::string FactoryConnectionComponent::vtypename() {
    return typeid(*this).name();
  }

  std::string FactoryConnectionComponent::compdetails() {
    return strprintf("ConnectedComponent: %s / %s\nConnectionInventory: %s / %s\nInventoryAccessIndex: %i\nDirection: %s\n",
		     c_mConnectedComponent.levelName().c_str(), c_mConnectedComponent.pathName().c_str(),
		     c_mConnectionInventory.levelName().c_str(), c_mConnectionInventory.pathName().c_str(),
		     c_mInventoryAccessIndex,
		     EnumDict<EFactoryConnectionDirection>::tostr(c_mDirection).c_str());
  }

  std::string FactoryConnectionComponent::str() {
    return compdetails();
  }

  void FactoryConnectionComponent::finalize() {
    c_mConnectedComponent.resolveInto(c_connectedcomponent);
    c_mConnectionInventory.resolveInto(c_connectioninventory);
    if ( !(c_building = std::dynamic_pointer_cast<Building>(parent())) ) {
      EXCEPTION(strprintf("Cannot cast parent to building: %s", instance().c_str()));
    }
  }

  bool FactoryConnectionComponent::send(DescObjectSP& _item, SFT::tickinfo_t& _tick) {
    if ( !c_connectedcomponent ) return false;
    return c_connectedcomponent->recv(_item, _tick);
  }

  bool FactoryConnectionComponent::recv(DescObjectSP& _item, SFT::tickinfo_t& _tick) {
    printf("%s\n on %s\n for %s \nInvComp: %s\n",
	   __PRETTY_FUNCTION__,
	   instance().c_str(), _item->className().c_str(),
	   c_connectioninventory?c_connectioninventory->instance().c_str():"none");
    // if we have a connection inventory, then put it there
    if ( c_connectioninventory ) {
      printf(" Inventorycomponent:\n%s\n\n", c_connectioninventory->compdetails().c_str());
    } else {
      // otherwise hand it over to our parent
      printf(" Calling building(%s)::recv\n", c_building->instance().c_str());
      return c_building->recv(_item, _tick, *this);
    }
    return true;
  }

}
