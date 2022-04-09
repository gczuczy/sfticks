
#include "FGBlender.hh"

namespace FG {

  std::string Blender::objtypename("Build_Blender_C");

  Blender::Blender(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::Blender, _reader, _fgoh){
    c_inputs.resize(2);
    c_outputs.resize(1);
    registerComponent("Input0", c_inputs[0]);
    registerComponent("Input1", c_inputs[1]);
    registerComponent("Output1", c_outputs[0]);
  }

  Blender::~Blender() {
  }

}
