
#include <stdio.h>

#include "FG/InventoryComponent.hh"

#include "FG/IntProperty.hh"
#include "FG/ArrayProperty.hh"
#include "FG/StructProperty.hh"
#include "FG/ObjectProperty.hh"
#include "FG/BoolProperty.hh"

namespace FG {

  std::set<std::string> InventoryComponent::pathname{
    "/Script/FactoryGame.InventoryComponent",
      "/Script/FactoryGame.FGInventoryComponent",
      };
  ComponentType InventoryComponent::componenttype(ComponentType::Inventory);

  InventoryComponent::InventoryComponent(Reader& _reader, ObjectHeader& _fgoh)
    : Component(ComponentType::Inventory, _reader, _fgoh) {
    defineProperty(std::make_shared<ArrayProperty<StructProperty<FG::InventoryStack> > >("mInventoryStacks", c_mInventoryStacks));
    defineProperty(std::make_shared<ArrayProperty<IntProperty> >("mArbitrarySlotSizes", c_mArbitrarySlotSizes));
    defineProperty(std::make_shared<ArrayProperty<ObjectProperty> >("mAllowedItemDescriptors", c_mAllowedItemDescriptors));
    defineProperty(std::make_shared<BoolProperty>("mCanBeRearrange", c_mCanBeRearrange));
    defineProperty(std::make_shared<IntProperty>("mAdjustedSizeDiff", c_mAdjustedSizeDiff));
  }

  void InventoryComponent::setStackSize(int32_t _size) {
    c_singlestacks = _size == 1;
    for (auto& it: c_inventorystacks) {
      it.size = _size;
    }
  }

  bool InventoryComponent::store(DescObjectSP& _item) {
    /* There are multiple rules here
       - If the stacksize=1 then we don't have to compare each
       counter, and no mergese are done, and no object comparisions are
       needed, which are slow
       - If the stacksize>1 then needs merging:
         - Needs same type of object
	 - Scan needed on the complete buffer, because any nonfull stack
	 of the same type is a viable target
     */
    if ( c_singlestacks ) {
      // if we are a single-size invstack. This is
      // generally belt attachment units, or boosting powerslugs
      for (auto&& it: c_inventorystacks) {
	// case is simple, if count=00 then putting it there
	if ( it.count == 0 ) {
	  it.item = _item;
	  return true;
	}
      }
      return false;
    } else {
      // now we have to check everything
      // TODO: we need an optimzed structure for this, this is
      // horribly ineffective

      // now check whether there's a non-full stack of the same type
      uint32_t emptyc=0;
      for (auto&& it: c_inventorystacks) {
	// count=0 means there's no stack in that position, skip
	if ( it.count == 0 ) {
	  emptyc += 1;
	  continue;
	}
	// skip full stacks
	if ( it.count == it.item->stackSize() ) continue;
	// skip items of a different type
	if ( *_item != *it.item ) continue;

	/* Right here, the following conditions are ensured:
	   - size not zero (= there is a stack here)
	   - stack is not full
	   - item type is the same
	 */
	it.count += 1;
	return true;
      }

      // We couldn't find a non-full stack, so now we need
      // to look for an empty slot

      // there are no empty slots
      if ( emptyc == 0 ) return false;

      for (auto&& it: c_inventorystacks) {
	if ( it.count != 0 ) continue;
	it.count = 1;
	it.item = _item;
	return true;
      }
    }
    return false;
  }

  ComponentSP InventoryComponent::instantiate(Reader& _reader, ObjectHeader& _fgoh) {
    return std::make_shared<InventoryComponent>(_reader, _fgoh);
  }

  std::string InventoryComponent::vtypename() {
    return typeid(*this).name();
  }

  std::string InventoryComponent::compdetails() {
    std::string rv;

    rv = strprintf("CanBeRearrange: %s\nAdjustedSizeDiff: %i\nSinglestacks: %s\nInventoryStacks:\n",
		   c_mCanBeRearrange?"yes":"no",
		   c_mAdjustedSizeDiff,
		   c_singlestacks?"yes":"no");

    if ( c_inventorystacks.size()>0 ) {
      for (auto it: c_inventorystacks) {
	rv += strprintf(" - %i/%i x %s\n", it.count, it.size, it.item->className().c_str());
      }
    } else {
      for (auto it: c_mInventoryStacks)
	rv += strprintf(" - %i x %s\n", it.NumItems, it.Item.ItemType.c_str());

      rv += strprintf("ArbitrarySlotSizes:");
      for (auto it: c_mArbitrarySlotSizes)
	rv += strprintf(" %i", it);
    }
    rv += strprintf("\nAllowedItemDescriptors:\n");
    for (auto it: c_mAllowedItemDescriptors)
      rv += strprintf(" - %s:%s\n",
		      it.levelName().c_str(),
		      it.pathName().c_str());

    return rv;
  }

  void InventoryComponent::finalize() {
    c_alloweditemdescriptors.resize(c_mAllowedItemDescriptors.size());
    for (int i=0; i<c_mAllowedItemDescriptors.size(); ++i) {
      // for now I have no idea how to handle FGItemDescriptor, as it's a class for settting
      // a category of items
      // and the Desc_ResourceSinkCoupon_C's def seems to be entirely missing from Docs.json
      if ( c_mAllowedItemDescriptors[i].pathName() != "/Script/FactoryGame.FGItemDescriptor" &&
	   c_mAllowedItemDescriptors[i].pathName() != "/Game/FactoryGame/Resource/Parts/ResourceSinkCoupon/Desc_ResourceSinkCoupon.Desc_ResourceSinkCoupon_C" )
	c_mAllowedItemDescriptors[i].resolveInto(c_alloweditemdescriptors[i]);
    } // for allowed item descr

    // inventory stacks
    c_inventorystacks.resize(c_mInventoryStacks.size());
    c_singlestacks = true;
    for (int i=0; i<c_mInventoryStacks.size(); ++i) {
      if ( c_mInventoryStacks[i].Item.ItemType != "" ) {
	ObjectReference("", c_mInventoryStacks[i].Item.ItemType).resolveInto(c_inventorystacks[i].item);
	c_inventorystacks[i].count = c_mInventoryStacks[i].NumItems;
	c_inventorystacks[i].size = c_mArbitrarySlotSizes[i];
	c_singlestacks &= c_mArbitrarySlotSizes[i] == 1;
      }
    }
  };
}
