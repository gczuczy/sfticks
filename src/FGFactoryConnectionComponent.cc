
#include "FGFactoryConnectionComponent.hh"

#include "ObjectProperty.hh"
#include "EnumProperty.hh"
#include "IntProperty.hh"

std::string FGFactoryConnectionComponent::pathname("/Script/FactoryGame.FGFactoryConnectionComponent");

FGFactoryConnectionComponent::FGFactoryConnectionComponent(Reader& _reader, FGObjectHeader& _fgoh)
  : FGComponent(FGComponentType::FactoryConnection, _reader, _fgoh),
    c_mDirection(EFactoryConnectionDirection::FCD_INPUT) {

  defineProperty(std::make_shared<ObjectProperty>("mConnectedComponent", c_mConnectedComponent));
  defineProperty(std::make_shared<ObjectProperty>("mConnectionInventory", c_mConnectionInventory));
  defineProperty(std::make_shared<EnumProperty<EFactoryConnectionDirection> >("mDirection", c_mDirection));
  defineProperty(std::make_shared<IntProperty>("mInventoryAccessIndex", c_mInventoryAccessIndex));
  //defineProperty(std::make_shared<ObjectProperty>("mConnectedComponent", c_mConnectedComponent));
}

FGComponentSP FGFactoryConnectionComponent::instantiate(Reader& _reader, FGObjectHeader& _fgoh) {
  return std::make_shared<FGFactoryConnectionComponent>(_reader, _fgoh);
}

