
#include "FGConveyorAttachmentSplitterSmart.hh"
#include "ArrayProperty.hh"
#include "StructProperty.hh"

std::string FGConveyorAttachmentSplitterSmart::objtypename("Build_ConveyorAttachmentSplitterSmart_C");

FGConveyorAttachmentSplitterSmart::FGConveyorAttachmentSplitterSmart(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorAttachmentSplitter(FGEntityType::ConveyorAttachmentSplitterSmart, _reader, _fgoh) {
  defineProperty(std::make_shared<ArrayProperty<StructProperty<SplitterSortRule> > >("mSortRules", c_mSortRules));
}

FGConveyorAttachmentSplitterSmart::~FGConveyorAttachmentSplitterSmart() {
}

