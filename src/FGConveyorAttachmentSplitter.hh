
#ifndef SFT_FGCONVEYATTACHMENTSPLITTER_H
#define SFT_FGCONVEYATTACHMENTSPLITTER_H

#include "FGConveyorBeltLogic.hh"
#include "SortRule.hh"
#include "ObjectReference.hh"

#include <map>

class FGConveyorAttachmentSplitter: public FGConveyorBeltLogic {
public:
  FGConveyorAttachmentSplitter()=delete;
  FGConveyorAttachmentSplitter(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorAttachmentSplitter();
protected:
  FGConveyorAttachmentSplitter(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh);

public:
  inline int32_t& mCurrentOutputIndex() {return c_mCurrentOutputIndex;};
  inline int32_t& mLastOutputIndex() {return c_mLastOutputIndex;};
  // TODO: add lookup call for mItemToLastOutputMap

private:
  void defProps();

private:
  //virtual void deserialize(Reader &_reader);
  int32_t c_mCurrentOutputIndex, c_mLastOutputIndex;
  std::map<ObjectReference, int8_t> c_mItemToLastOutputMap;
};

#endif
