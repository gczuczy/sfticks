
#include "FGFactoryConnectionComponent.hh"

#include "ObjectProperty.hh"
#include "EnumProperty.hh"
#include "IntProperty.hh"

namespace FG {

  std::set<std::string> FactoryConnectionComponent::pathname{
    "/Script/FactoryGame.FactoryConnectionComponent",
      "/Script/FactoryGame.FGFactoryConnectionComponent",
      };
  ComponentType FactoryConnectionComponent::componenttype(ComponentType::FactoryConnection);

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

  std::string FactoryConnectionComponent::vtypename() {
    return typeid(*this).name();
  }

#if 0
  std::string FGFactoryConnectionComponent::pathname("/Script/FactoryGame.FGFactoryConnectionComponent");
  FGFactoryConnectionComponent::FGFactoryConnectionComponent(Reader& _reader, ObjectHeader& _fgoh)
    :FactoryConnectionComponent(_reader, _fgoh) {
  }

  std::string FGFactoryConnectionComponent::vtypename() {
    return typeid(*this).name();
  }
#endif
}
