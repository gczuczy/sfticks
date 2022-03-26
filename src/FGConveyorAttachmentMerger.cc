
#include "FGConveyorAttachmentMerger.hh"

FGConveyorAttachmentMerger::FGConveyorAttachmentMerger(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorBeltLogic(FGEntityType::ConveyorAttachmentMerger, _reader, _fgoh), c_mCurrentInputIndex(0), c_mCurrentInventoryIndex(0) {
  defineProperty("mCurrentInputIndex", "IntProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mCurrentInputIndex);});
  defineProperty("mCurrentInventoryIndex", "IntProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mCurrentInventoryIndex);});
}

FGConveyorAttachmentMerger::~FGConveyorAttachmentMerger() {
}

