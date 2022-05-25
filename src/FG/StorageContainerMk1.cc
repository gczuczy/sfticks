
#include "FG/StorageContainerMk1.hh"

namespace FG {

  std::string StorageContainerMk1::objtypename("Build_StorageContainerMk1_C");

  StorageContainerMk1::StorageContainerMk1(Reader& _reader, ObjectHeader& _fgoh)
    : StorageUnit(EntityType::StorageContainerMk1, _reader, _fgoh, 24){
  }

  StorageContainerMk1::~StorageContainerMk1() {
  }

}
