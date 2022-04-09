
#include "FGConveyorAttachmentMerger.hh"

#include "IntProperty.hh"

namespace FG {

  std::string ConveyorAttachmentMerger::objtypename("Build_ConveyorAttachmentMerger_C");

  ConveyorAttachmentMerger::ConveyorAttachmentMerger(Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorBeltLogic(EntityType::ConveyorAttachmentMerger, _reader, _fgoh), c_mCurrentInputIndex(0), c_mCurrentInventoryIndex(0) {
    defineProperty(std::make_shared<IntProperty>("mCurrentInputIndex", c_mCurrentInputIndex));
    defineProperty(std::make_shared<IntProperty>("mCurrentInventoryIndex", c_mCurrentInventoryIndex));

    //components
    c_inputs.resize(3);
    c_outputs.resize(1);
    registerComponent("Input1", c_inputs[0]);
    registerComponent("Input2", c_inputs[1]);
    registerComponent("InPut3", c_inputs[2]);
    registerComponent("Output1", c_outputs[0]);
  }

  ConveyorAttachmentMerger::~ConveyorAttachmentMerger() {
  }

}
