
#include "FGConveyorAttachmentSplitter.hh"
#include "IntProperty.hh"

FGConveyorAttachmentSplitter::FGConveyorAttachmentSplitter(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorBeltLogic(FGEntityType::ConveyorAttachmentSplitter, _reader, _fgoh), c_mCurrentOutputIndex(0) {
  defineProperty(std::make_shared<IntProperty>("mCurrentOutputIndex", c_mCurrentOutputIndex));
}

FGConveyorAttachmentSplitter::~FGConveyorAttachmentSplitter() {
}

