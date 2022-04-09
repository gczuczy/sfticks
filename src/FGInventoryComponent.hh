
#ifndef SFT_FGINVENTORYCOMPONENT_H
#define SFT_FGINVENTORYCOMPONENT_H

#include "FGComponent.hh"
#include "InventoryStack.hh"
#include "ObjectReference.hh"

#include <vector>

namespace FG {

  class InventoryComponent: public Component {
  public:
    InventoryComponent() = delete;
    InventoryComponent(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~InventoryComponent()=default;
    static ComponentSP instantiate(Reader& _reader, ObjectHeader& _fgoh);

  public:
    static std::string pathname;

  private:
    std::vector<InventoryStack> c_mInventoryStacks;
    std::vector<int32_t> c_mArbitrarySlotSizes;
    std::vector<ObjectReference> c_mAllowedItemDescriptors;
    bool c_mCanBeRearrange;
    int32_t c_mAdjustedSizeDiff;
  };
  typedef std::shared_ptr<InventoryComponent> InventoryComponentSP;

}

#endif
