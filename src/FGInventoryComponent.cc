
#include "FGInventoryComponent.hh"

#include "IntProperty.hh"
#include "ArrayProperty.hh"
#include "StructProperty.hh"
#include "ObjectProperty.hh"
#include "BoolProperty.hh"

namespace FG {

  std::set<std::string> InventoryComponent::pathname{
    "/Script/FactoryGame.InventoryComponent",
      "/Script/FactoryGame.FGInventoryComponent",
      };
  ComponentType InventoryComponent::componenttype(ComponentType::Inventory);

  InventoryComponent::InventoryComponent(Reader& _reader, ObjectHeader& _fgoh)
    : Component(ComponentType::Inventory, _reader, _fgoh) {
    defineProperty(std::make_shared<ArrayProperty<StructProperty<InventoryStack> > >("mInventoryStacks", c_mInventoryStacks));
    defineProperty(std::make_shared<ArrayProperty<IntProperty> >("mArbitrarySlotSizes", c_mArbitrarySlotSizes));
    defineProperty(std::make_shared<ArrayProperty<ObjectProperty> >("mAllowedItemDescriptors", c_mAllowedItemDescriptors));
    defineProperty(std::make_shared<BoolProperty>("mCanBeRearrange", c_mCanBeRearrange));
    defineProperty(std::make_shared<IntProperty>("mAdjustedSizeDiff", c_mAdjustedSizeDiff));
  }

  ComponentSP InventoryComponent::instantiate(Reader& _reader, ObjectHeader& _fgoh) {
    return std::make_shared<InventoryComponent>(_reader, _fgoh);
  }

  std::string InventoryComponent::vtypename() {
    return typeid(*this).name();
  }

  std::string InventoryComponent::compdetails() {
    std::string rv;

    rv = strprintf("CanBeRearrange: %s\nAdjustedSizeDiff: %i\nInventoryStacks:\n",
		   c_mCanBeRearrange?"yes":"no", c_mAdjustedSizeDiff);

    for (auto it: c_mInventoryStacks)
      rv += strprintf(" - %i x %s\n", it.NumItems, it.Item.ItemType.c_str());

    rv += strprintf("ArbitrarySlotSizes:");
    for (auto it: c_mArbitrarySlotSizes)
      rv += strprintf(" %i", it);

    rv += strprintf("\nAllowedItemDescriptors:\n");
    for (auto it: c_mAllowedItemDescriptors)
      rv += strprintf(" - %s:%s\n",
		      it.levelName().c_str(),
		      it.pathName().c_str());

    return rv;
  }
}
