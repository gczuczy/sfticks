
#include "FGConveyorAttachmentSplitter.hh"
#include "IntProperty.hh"
#include "ByteProperty.hh"
#include "MapProperty.hh"
#include "ObjectProperty.hh"

namespace FG {

  std::string ConveyorAttachmentSplitter::objtypename("Build_ConveyorAttachmentSplitter_C");

  ConveyorAttachmentSplitter::ConveyorAttachmentSplitter(Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorBeltLogic(EntityType::ConveyorAttachmentSplitter, _reader, _fgoh), c_mCurrentOutputIndex(0),
      c_mLastOutputIndex(0) {
    defProps();
  }

  ConveyorAttachmentSplitter::ConveyorAttachmentSplitter(EntityType _et, Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorBeltLogic(_et, _reader, _fgoh), c_mCurrentOutputIndex(0), c_mLastOutputIndex(0) {
    defProps();
  }

  ConveyorAttachmentSplitter::~ConveyorAttachmentSplitter() {
  }

  void ConveyorAttachmentSplitter::defProps() {
    defineProperty(std::make_shared<IntProperty>("mCurrentOutputIndex", c_mCurrentOutputIndex));
    defineProperty(std::make_shared<IntProperty>("mLastOutputIndex", c_mLastOutputIndex));
    defineProperty(std::make_shared<MapProperty<ObjectProperty, ByteProperty> >("mItemToLastOutputMap", c_mItemToLastOutputMap));

    //components
    defineInputs({"Input1"});
    defineOutputs({"Output1", "Output2", "Output3"});
  }

}
