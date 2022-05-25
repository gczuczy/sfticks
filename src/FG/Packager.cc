
#include "FG/Packager.hh"

namespace FG {

  std::string Packager::objtypename("Build_Packager_C");

  Packager::Packager(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::Packager, _reader, _fgoh){
  }

  Packager::~Packager() {
  }

}
