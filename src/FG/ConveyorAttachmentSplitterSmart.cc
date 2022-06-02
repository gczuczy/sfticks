
#include "FG/ConveyorAttachmentSplitterSmart.hh"
#include "FG/ArrayProperty.hh"
#include "FG/StructProperty.hh"
#include "SFT/Exception.hh"
#include "misc.hh"

namespace FG {

  std::string ConveyorAttachmentSplitterSmart::objtypename("Build_ConveyorAttachmentSplitterSmart_C");

  ConveyorAttachmentSplitterSmart::ConveyorAttachmentSplitterSmart(Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorAttachmentSplitter(EntityType::ConveyorAttachmentSplitterSmart, _reader, _fgoh) {
    defineProperty(std::make_shared<ArrayProperty<StructProperty<SplitterSortRule> > >("mSortRules", c_mSortRules));
  }

  ConveyorAttachmentSplitterSmart::~ConveyorAttachmentSplitterSmart() {
  }

  void ConveyorAttachmentSplitterSmart::doTick(SFT::tickinfo_t& _tick) {
    EXCEPTION(strprintf("Check %s", __PRETTY_FUNCTION__));
  }

}
