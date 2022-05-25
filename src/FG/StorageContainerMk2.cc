
#include "FG/StorageContainerMk2.hh"

namespace FG {

  std::string StorageContainerMk2::objtypename("Build_StorageContainerMk2_C");

  StorageContainerMk2::StorageContainerMk2(Reader& _reader, ObjectHeader& _fgoh)
    : StorageUnit(EntityType::StorageContainerMk2, _reader, _fgoh, 48){
  }

  StorageContainerMk2::~StorageContainerMk2() {
  }

}
