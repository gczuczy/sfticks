
#ifndef SFT_FGCONVEYATTACHMENTSPLITTER_H
#define SFT_FGCONVEYATTACHMENTSPLITTER_H

#include "FGConveyorBeltLogic.hh"
#include "SortRule.hh"
#include "ObjectReference.hh"

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
    inline int32_t& mCurrentOutputIndex() {return c_mCurrentOutputIndex;};
    inline int32_t& mLastOutputIndex() {return c_mLastOutputIndex;};
    // TODO: add lookup call for mItemToLastOutputMap

    static std::string objtypename;

  private:
    void defProps();

  private:
    //virtual void deserialize(Reader &_reader);
    int32_t c_mCurrentOutputIndex, c_mLastOutputIndex;
    std::map<ObjectReference, int8_t> c_mItemToLastOutputMap;
  };

}

#endif
