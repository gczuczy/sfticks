
#include "FGStorageContainerMk1.hh"

std::string FGStorageContainerMk1::objtypename("Build_StorageContainerMk1_C");

FGStorageContainerMk1::FGStorageContainerMk1(Reader& _reader, FGObjectHeader& _fgoh)
  : FGStorageUnit(FGEntityType::StorageContainerMk1, _reader, _fgoh, 24){
}

FGStorageContainerMk1::~FGStorageContainerMk1() {
}

