
#ifndef SFT_FGINVENTORYCOMPONENT_H
#define SFT_FGINVENTORYCOMPONENT_H

#include "FGComponent.hh"
#include "InventoryStack.hh"
#include "ObjectReference.hh"

#include <vector>
#include <set>

namespace FG {

  class InventoryComponent: public Component {
  public:
    InventoryComponent() = delete;
    InventoryComponent(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~InventoryComponent()=default;
    static ComponentSP instantiate(Reader& _reader, ObjectHeader& _fgoh);

    virtual std::string vtypename();

  public:
    static std::set<std::string> pathname;
    static ComponentType componenttype;

  private:
    std::vector<InventoryStack> c_mInventoryStacks;
    std::vector<int32_t> c_mArbitrarySlotSizes;
    std::vector<ObjectReference> c_mAllowedItemDescriptors;
    bool c_mCanBeRearrange;
    int32_t c_mAdjustedSizeDiff;
  };
  typedef std::shared_ptr<InventoryComponent> InventoryComponentSP;

#if 0
  class FGInventoryComponent: public InventoryComponent {
  public:
  public:
    FGInventoryComponent() = delete;
    FGInventoryComponent(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~FGInventoryComponent()=default;
    virtual std::string vtypename();

    static std::string pathname;
  };
#endif
}

#endif
