
#include "FG/SmelterMk1.hh"

namespace FG {

  std::string SmelterMk1::objtypename("Build_SmelterMk1_C");

  SmelterMk1::SmelterMk1(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::SmelterMk1, _reader, _fgoh){
    defineInputs({"Input0"});
    defineOutputs({"Output2"});
  }

  SmelterMk1::~SmelterMk1() {
  }

}
