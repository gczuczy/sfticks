
#ifndef SFT_FGSTORAGECONTAINERMK1_H
#define SFT_FGSTORAGECONTAINERMK1_H

#include "FGStorageUnit.hh"

class FGStorageContainerMk1: public FGStorageUnit {
public:
  FGStorageContainerMk1()=delete;
  FGStorageContainerMk1(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGStorageContainerMk1();

  static std::string objtypename;

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
