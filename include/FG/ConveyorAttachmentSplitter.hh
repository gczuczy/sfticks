
#ifndef SFT_FGCONVEYATTACHMENTSPLITTER_H
#define SFT_FGCONVEYATTACHMENTSPLITTER_H

#include "FG/ConveyorBeltLogic.hh"
#include "FG/SortRule.hh"
#include "FG/ObjectReference.hh"

#include <map>

namespace FG {

  class ConveyorAttachmentSplitter: public ConveyorBeltLogic {
  public:
    ConveyorAttachmentSplitter()=delete;
    ConveyorAttachmentSplitter(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ConveyorAttachmentSplitter();
  protected:
    ConveyorAttachmentSplitter(EntityType _et, Reader& _reader, ObjectHeader& _fgoh);

  public:
    inline int32_t& currentOutputIndex() {return c_mCurrentOutputIndex;};
    inline int32_t& lastOutputIndex() {return c_mLastOutputIndex;};
    // TODO: add lookup call for mItemToLastOutputMap

    virtual void doTick(SFT::tickinfo_t& _tick);

    static std::string objtypename;

  private:
    void defProps();

  private:
    //virtual void deserialize(Reader &_reader);
    int32_t c_mCurrentOutputIndex, c_mLastOutputIndex;
    std::map<ObjectReference, int8_t> c_mItemToLastOutputMap;
  };
  typedef std::shared_ptr<ConveyorAttachmentSplitter> ConveyorAttachmentSplitterSP;

}

#endif
