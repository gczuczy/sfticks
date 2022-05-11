
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

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
    int32_t c_mCurrentInputIndex, c_mCurrentInventoryIndex;
  };
  typedef std::shared_ptr<ConveyorAttachmentMerger> ConveyorAttachmentMergerSP;

}

#endif
