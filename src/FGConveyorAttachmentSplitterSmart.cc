
#include "FGConveyorAttachmentSplitterSmart.hh"
#include "ArrayProperty.hh"
#include "StructProperty.hh"

namespace FG {

  std::string ConveyorAttachmentSplitterSmart::objtypename("Build_ConveyorAttachmentSplitterSmart_C");

  ConveyorAttachmentSplitterSmart::ConveyorAttachmentSplitterSmart(Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorAttachmentSplitter(EntityType::ConveyorAttachmentSplitterSmart, _reader, _fgoh) {
    defineProperty(std::make_shared<ArrayProperty<StructProperty<SplitterSortRule> > >("mSortRules", c_mSortRules));
  }

  ConveyorAttachmentSplitterSmart::~ConveyorAttachmentSplitterSmart() {
  }

}
