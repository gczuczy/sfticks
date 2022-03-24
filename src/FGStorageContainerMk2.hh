
#ifndef SFT_FGSTORAGECONTAINERMK2_H
#define SFT_FGSTORAGECONTAINERMK2_H

#include "FGStorageUnit.hh"

class FGStorageContainerMk2: public FGStorageUnit {
public:
  FGStorageContainerMk2()=delete;
  FGStorageContainerMk2(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGStorageContainerMk2();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
