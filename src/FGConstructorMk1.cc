
#include "FGConstructorMk1.hh"
#include "Exception.hh"
#include "Trace.hh"

#include <cassert>

namespace FG {

  std::string ConstructorMk1::objtypename("Build_ConstructorMk1_C");

  ConstructorMk1::ConstructorMk1(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::ConstructorMk1, _reader, _fgoh) {
    defineInputs({"Input0"});
    defineOutputs({"Output0"});
  }

  ConstructorMk1::~ConstructorMk1() {
  }

}
