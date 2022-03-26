
#include "FGConveyorAttachmentSplitter.hh"

FGConveyorAttachmentSplitter::FGConveyorAttachmentSplitter(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorBeltLogic(FGEntityType::ConveyorAttachmentSplitter, _reader, _fgoh), c_mCurrentOutputIndex(0) {
  defineProperty("mCurrentOutputIndex", "IntProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mCurrentOutputIndex);});
}

FGConveyorAttachmentSplitter::~FGConveyorAttachmentSplitter() {
}

