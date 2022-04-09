
#include "FGFactoryConnectionComponent.hh"

#include "ObjectProperty.hh"
#include "EnumProperty.hh"
#include "IntProperty.hh"

namespace FG {

  std::string FactoryConnectionComponent::pathname("/Script/FactoryGame.FactoryConnectionComponent");

  FactoryConnectionComponent::FactoryConnectionComponent(Reader& _reader, ObjectHeader& _fgoh)
    : Component(ComponentType::FactoryConnection, _reader, _fgoh),
      c_mDirection(EFactoryConnectionDirection::FCD_INPUT) {

    defineProperty(std::make_shared<ObjectProperty>("mConnectedComponent", c_mConnectedComponent));
    defineProperty(std::make_shared<ObjectProperty>("mConnectionInventory", c_mConnectionInventory));
    defineProperty(std::make_shared<EnumProperty<EFactoryConnectionDirection> >("mDirection", c_mDirection));
    defineProperty(std::make_shared<IntProperty>("mInventoryAccessIndex", c_mInventoryAccessIndex));
    //defineProperty(std::make_shared<ObjectProperty>("mConnectedComponent", c_mConnectedComponent));
  }

  ComponentSP FactoryConnectionComponent::instantiate(Reader& _reader, ObjectHeader& _fgoh) {
    return std::make_shared<FactoryConnectionComponent>(_reader, _fgoh);
  }

}
