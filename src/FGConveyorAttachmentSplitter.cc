
#include "FGConveyorAttachmentSplitter.hh"
#include "IntProperty.hh"

FGConveyorAttachmentSplitter::FGConveyorAttachmentSplitter(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorBeltLogic(FGEntityType::ConveyorAttachmentSplitter, _reader, _fgoh), c_mCurrentOutputIndex(0),
    c_mLastOutputIndex(0) {
  defProps();
}

FGConveyorAttachmentSplitter::FGConveyorAttachmentSplitter(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorBeltLogic(_et, _reader, _fgoh), c_mCurrentOutputIndex(0), c_mLastOutputIndex(0) {
  defProps();
}

FGConveyorAttachmentSplitter::~FGConveyorAttachmentSplitter() {
}

void FGConveyorAttachmentSplitter::defProps() {
  defineProperty(std::make_shared<IntProperty>("mCurrentOutputIndex", c_mCurrentOutputIndex));
  defineProperty(std::make_shared<IntProperty>("mLastOutputIndex", c_mLastOutputIndex));
}
