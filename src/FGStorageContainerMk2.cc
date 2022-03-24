
#include "FGStorageContainerMk2.hh"

FGStorageContainerMk2::FGStorageContainerMk2(Reader& _reader, FGObjectHeader& _fgoh)
  : FGStorageUnit(FGEntityType::StorageContainerMk2, _reader, _fgoh, 48){
}

FGStorageContainerMk2::~FGStorageContainerMk2() {
}

