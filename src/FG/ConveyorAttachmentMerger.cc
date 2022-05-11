
#include "FG/ConveyorAttachmentMerger.hh"

#include "FG/IntProperty.hh"

namespace FG {

  std::string ConveyorAttachmentMerger::objtypename("Build_ConveyorAttachmentMerger_C");

  ConveyorAttachmentMerger::ConveyorAttachmentMerger(Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorBeltLogic(EntityType::ConveyorAttachmentMerger, _reader, _fgoh), c_mCurrentInputIndex(0), c_mCurrentInventoryIndex(0) {
    defineProperty(std::make_shared<IntProperty>("mCurrentInputIndex", c_mCurrentInputIndex));
    defineProperty(std::make_shared<IntProperty>("mCurrentInventoryIndex", c_mCurrentInventoryIndex));

    //components
    defineInputs({"Input1", "Input2", "InPut3"});
    defineOutputs({"Output1"});
  }

  ConveyorAttachmentMerger::~ConveyorAttachmentMerger() {
  }

}
