
#include "FGInventoryComponent.hh"

#include "IntProperty.hh"
#include "ArrayProperty.hh"
#include "StructProperty.hh"
#include "ObjectProperty.hh"
#include "BoolProperty.hh"

namespace FG {

  std::string InventoryComponent::pathname("/Script/FactoryGame.InventoryComponent");

  InventoryComponent::InventoryComponent(Reader& _reader, ObjectHeader& _fgoh)
    : Component(ComponentType::Inventory, _reader, _fgoh), c_mCanBeRearrange(false), c_mAdjustedSizeDiff(0) {
    defineProperty(std::make_shared<ArrayProperty<StructProperty<InventoryStack> > >("mInventoryStacks", c_mInventoryStacks));
    defineProperty(std::make_shared<ArrayProperty<IntProperty> >("mArbitrarySlotSizes", c_mArbitrarySlotSizes));
    defineProperty(std::make_shared<ArrayProperty<ObjectProperty> >("mAllowedItemDescriptors", c_mAllowedItemDescriptors));
    defineProperty(std::make_shared<BoolProperty>("mCanBeRearrange", c_mCanBeRearrange));
    defineProperty(std::make_shared<IntProperty>("mAdjustedSizeDiff", c_mAdjustedSizeDiff));
  }

  ComponentSP InventoryComponent::instantiate(Reader& _reader, ObjectHeader& _fgoh) {
    return std::make_shared<InventoryComponent>(_reader, _fgoh);
  }

}
