
#ifndef SFT_FGCONVEYATTACHMENTSPLITTER_H
#define SFT_FGCONVEYATTACHMENTSPLITTER_H

#include "FGConveyorBeltLogic.hh"
#include "SortRule.hh"

class FGConveyorAttachmentSplitter: public FGConveyorBeltLogic {
public:
  FGConveyorAttachmentSplitter()=delete;
  FGConveyorAttachmentSplitter(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorAttachmentSplitter();

  inline int32_t& mCurrentOutputIndex() {return c_mCurrentOutputIndex;};
  inline int32_t& mLastOutputIndex() {return c_mLastOutputIndex;};

private:
  //virtual void deserialize(Reader &_reader);
  int32_t c_mCurrentOutputIndex, c_mLastOutputIndex;
};

#endif
