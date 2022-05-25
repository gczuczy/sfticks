
#include "FG/ConstructorMk1.hh"
#include "SFT/Exception.hh"
#include "SFT/Trace.hh"

#include <cassert>

namespace FG {

  std::string ConstructorMk1::objtypename("Build_ConstructorMk1_C");

  ConstructorMk1::ConstructorMk1(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::ConstructorMk1, _reader, _fgoh) {
  }

  ConstructorMk1::~ConstructorMk1() {
  }

}
