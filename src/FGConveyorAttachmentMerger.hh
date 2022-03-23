
#ifndef SFT_FGCONVEYATTACHMENTMERGER_H
#define SFT_FGCONVEYATTACHMENTMERGER_H

#include "FGConveyorBeltLogic.hh"

class FGConveyorAttachmentMerger: public FGConveyorBeltLogic {
public:
  FGConveyorAttachmentMerger()=delete;
  FGConveyorAttachmentMerger(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorAttachmentMerger();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
