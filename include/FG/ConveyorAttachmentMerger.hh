
#ifndef SFT_FGCONVEYATTACHMENTMERGER_H
#define SFT_FGCONVEYATTACHMENTMERGER_H

#include "FG/ConveyorBeltLogic.hh"

namespace FG {

  class ConveyorAttachmentMerger: public ConveyorBeltLogic {
  public:
    ConveyorAttachmentMerger()=delete;
    ConveyorAttachmentMerger(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ConveyorAttachmentMerger();

    inline int32_t& currentInputIndex() {return c_mCurrentInputIndex;};
    inline int32_t& currentInventoryIndex() {return c_mCurrentInventoryIndex;};

    virtual void associateComponents();
    virtual void doTick(SFT::tickinfo_t& _tick);
    virtual bool recv(DescObjectSP& _item, SFT::tickinfo_t& _tick, FactoryConnectionComponent& _src);

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
    int32_t c_mCurrentInputIndex=0, c_mCurrentInventoryIndex=0;
    // connected inputs
    std::vector<FactoryConnectionComponentSP> c_connected_inputs;
  };
  typedef std::shared_ptr<ConveyorAttachmentMerger> ConveyorAttachmentMergerSP;

}

#endif
