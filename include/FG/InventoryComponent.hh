
#ifndef SFT_FGINVENTORYCOMPONENT_H
#define SFT_FGINVENTORYCOMPONENT_H

#include "FG/Component.hh"
#include "FG/InventoryStack.hh"
#include "FG/ObjectReference.hh"
#include "FG/DescObject.hh"

#include <vector>
#include <set>

namespace FG {

  class InventoryComponent: public Component {
  public:
    struct InventoryStack {
      int32_t count=0;
      int32_t size=0;
      DescObjectSP item;
    };
  public:
    InventoryComponent() = delete;
    InventoryComponent(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~InventoryComponent()=default;
    static ComponentSP instantiate(Reader& _reader, ObjectHeader& _fgoh);

    void setStackSize(int32_t _size);
    bool store(DescObjectSP& _item);
    inline const std::vector<DescObjectSP>& allowedItemDescriptors() const {return c_alloweditemdescriptors;};
    inline std::vector<InventoryStack> inventoryStacks() {return c_inventorystacks;};

    virtual std::string vtypename();
    virtual std::string compdetails();
    virtual void finalize();

  public:
    static std::set<std::string> pathname;
    static ComponentType componenttype;

  private:
    std::vector<FG::InventoryStack> c_mInventoryStacks;
    std::vector<InventoryStack> c_inventorystacks;
    std::vector<int32_t> c_mArbitrarySlotSizes;
    std::vector<ObjectReference> c_mAllowedItemDescriptors;
    std::vector<DescObjectSP> c_alloweditemdescriptors;
    bool c_mCanBeRearrange=false;
    int32_t c_mAdjustedSizeDiff=0;
    bool c_singlestacks=false;
  };
  typedef std::shared_ptr<InventoryComponent> InventoryComponentSP;

}

#endif
