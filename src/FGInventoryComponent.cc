
#include "FGInventoryComponent.hh"

#include "IntProperty.hh"
#include "ArrayProperty.hh"
#include "StructProperty.hh"
#include "ObjectProperty.hh"
#include "BoolProperty.hh"

std::string FGInventoryComponent::pathname("/Script/FactoryGame.FGInventoryComponent");

FGInventoryComponent::FGInventoryComponent(Reader& _reader, FGObjectHeader& _fgoh)
  : FGComponent(FGComponentType::Inventory, _reader, _fgoh), c_mCanBeRearrange(false), c_mAdjustedSizeDiff(0) {
  defineProperty(std::make_shared<ArrayProperty<StructProperty<InventoryStack> > >("mInventoryStacks", c_mInventoryStacks));
  defineProperty(std::make_shared<ArrayProperty<IntProperty> >("mArbitrarySlotSizes", c_mArbitrarySlotSizes));
  defineProperty(std::make_shared<ArrayProperty<ObjectProperty> >("mAllowedItemDescriptors", c_mAllowedItemDescriptors));
  defineProperty(std::make_shared<BoolProperty>("mCanBeRearrange", c_mCanBeRearrange));
  defineProperty(std::make_shared<IntProperty>("mAdjustedSizeDiff", c_mAdjustedSizeDiff));
}

FGComponentSP FGInventoryComponent::instantiate(Reader& _reader, FGObjectHeader& _fgoh) {
  return std::make_shared<FGInventoryComponent>(_reader, _fgoh);
}
