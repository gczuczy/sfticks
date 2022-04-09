
#include "FGStorageContainerMk2.hh"

std::string FGStorageContainerMk2::objtypename("Build_StorageContainerMk2_C");

FGStorageContainerMk2::FGStorageContainerMk2(Reader& _reader, FGObjectHeader& _fgoh)
  : FGStorageUnit(FGEntityType::StorageContainerMk2, _reader, _fgoh, 48){
}

FGStorageContainerMk2::~FGStorageContainerMk2() {
}

