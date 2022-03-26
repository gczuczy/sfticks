
#ifndef SFT_FGCONVEYATTACHMENTSPLITTER_H
#define SFT_FGCONVEYATTACHMENTSPLITTER_H

#include "FGConveyorBeltLogic.hh"

class FGConveyorAttachmentSplitter: public FGConveyorBeltLogic {
public:
  FGConveyorAttachmentSplitter()=delete;
  FGConveyorAttachmentSplitter(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorAttachmentSplitter();

  inline int32_t& mCurrentOutputIndex() {return c_mCurrentOutputIndex;};


private:
  //virtual void deserialize(Reader &_reader);
  int32_t c_mCurrentOutputIndex;
};

#endif
