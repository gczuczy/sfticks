
#ifndef SFT_FGCONVEYATTACHMENTSPLITTERSMART_H
#define SFT_FGCONVEYATTACHMENTSPLITTERSMART_H

#include "FGConveyorBeltLogic.hh"
#include "SortRule.hh"

#include <vector>

class FGConveyorAttachmentSplitterSmart: public FGConveyorBeltLogic {
public:
  FGConveyorAttachmentSplitterSmart()=delete;
  FGConveyorAttachmentSplitterSmart(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorAttachmentSplitterSmart();

  inline std::vector<SplitterSortRule>& mSortRules() {return c_mSortRules;};

private:
  //std::vector<> c_mSortRules;
  //virtual void deserialize(Reader &_reader);
  std::vector<SplitterSortRule> c_mSortRules;
};

#endif
