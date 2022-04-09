
#include "FGManufacturerMk1.hh"

namespace FG {

  std::string ManufacturerMk1::objtypename("Build_ManufacturerMk1_C");

  ManufacturerMk1::ManufacturerMk1(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::ManufacturerMk1, _reader, _fgoh) {
  }

  ManufacturerMk1::~ManufacturerMk1() {
  }

}
