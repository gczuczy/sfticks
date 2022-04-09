
#include "FGPackager.hh"

namespace FG {

  std::string Packager::objtypename("Build_Packager_C");

  Packager::Packager(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::Packager, _reader, _fgoh){
    c_inputs.resize(1);
    c_outputs.resize(1);
    registerComponent("Input0", c_inputs[0]);
    registerComponent("Output1", c_outputs[0]);
  }

  Packager::~Packager() {
  }

}
