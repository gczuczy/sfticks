
#ifndef SFT_FGCONVEYATTACHMENTSPLITTER_H
#define SFT_FGCONVEYATTACHMENTSPLITTER_H

#include "FGConveyorBeltLogic.hh"

class FGConveyorAttachmentSplitter: public FGConveyorBeltLogic {
public:
  FGConveyorAttachmentSplitter()=delete;
  FGConveyorAttachmentSplitter(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorAttachmentSplitter();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
