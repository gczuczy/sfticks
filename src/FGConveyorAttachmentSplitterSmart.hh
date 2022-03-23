
#ifndef SFT_FGCONVEYATTACHMENTSPLITTERSMART_H
#define SFT_FGCONVEYATTACHMENTSPLITTERSMART_H

#include "FGConveyorBeltLogic.hh"

class FGConveyorAttachmentSplitterSmart: public FGConveyorBeltLogic {
public:
  FGConveyorAttachmentSplitterSmart()=delete;
  FGConveyorAttachmentSplitterSmart(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorAttachmentSplitterSmart();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
