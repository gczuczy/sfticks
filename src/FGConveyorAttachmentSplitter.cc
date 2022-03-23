
#include "FGConveyorAttachmentSplitter.hh"

FGConveyorAttachmentSplitter::FGConveyorAttachmentSplitter(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorBeltLogic(FGEntityType::ConveyorAttachmentSplitter, _reader, _fgoh) {
}

FGConveyorAttachmentSplitter::~FGConveyorAttachmentSplitter() {
}

