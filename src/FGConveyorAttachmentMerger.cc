
#include "FGConveyorAttachmentMerger.hh"

FGConveyorAttachmentMerger::FGConveyorAttachmentMerger(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorBeltLogic(FGEntityType::ConveyorAttachmentMerger, _reader, _fgoh) {
}

FGConveyorAttachmentMerger::~FGConveyorAttachmentMerger() {
}

