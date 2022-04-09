
#ifndef SFT_FGINVENTORYCOMPONENT_H
#define SFT_FGINVENTORYCOMPONENT_H

#include "FGComponent.hh"
#include "InventoryStack.hh"
#include "ObjectReference.hh"

#include <vector>

class FGInventoryComponent: public FGComponent {
public:
  FGInventoryComponent() = delete;
  FGInventoryComponent(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGInventoryComponent()=default;
  static FGComponentSP instantiate(Reader& _reader, FGObjectHeader& _fgoh);

public:
  static std::string pathname;

private:
  std::vector<InventoryStack> c_mInventoryStacks;
  std::vector<int32_t> c_mArbitrarySlotSizes;
  std::vector<ObjectReference> c_mAllowedItemDescriptors;
  bool c_mCanBeRearrange;
  int32_t c_mAdjustedSizeDiff;
};

#endif
