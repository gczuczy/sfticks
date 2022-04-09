
#ifndef SFT_FGCONVEYATTACHMENTMERGER_H
#define SFT_FGCONVEYATTACHMENTMERGER_H

#include "FGConveyorBeltLogic.hh"

class FGConveyorAttachmentMerger: public FGConveyorBeltLogic {
public:
  FGConveyorAttachmentMerger()=delete;
  FGConveyorAttachmentMerger(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorAttachmentMerger();

  inline int32_t& mCurrentInputIndex() {return c_mCurrentInputIndex;};
  inline int32_t& mCurrentInventoryIndex() {return c_mCurrentInventoryIndex;};

  static std::string objtypename;

private:
  //virtual void deserialize(Reader &_reader);
  int32_t c_mCurrentInputIndex, c_mCurrentInventoryIndex;
};

#endif
