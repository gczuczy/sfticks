
#ifndef SFT_FGCONVEYATTACHMENTSPLITTERSMART_H
#define SFT_FGCONVEYATTACHMENTSPLITTERSMART_H

#include "FG/ConveyorAttachmentSplitter.hh"
#include "FG/SortRule.hh"

#include <vector>

namespace FG {

  class ConveyorAttachmentSplitterSmart: public ConveyorAttachmentSplitter {
  public:
    ConveyorAttachmentSplitterSmart()=delete;
    ConveyorAttachmentSplitterSmart(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ConveyorAttachmentSplitterSmart();

    inline std::vector<SplitterSortRule>& mSortRules() {return c_mSortRules;};

    virtual void doTick(SFT::tickinfo_t& _tick);

    static std::string objtypename;

  private:
    //std::vector<> c_mSortRules;
    //virtual void deserialize(Reader &_reader);
    std::vector<SplitterSortRule> c_mSortRules;
  };

}

#endif
