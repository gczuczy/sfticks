
#ifndef SFT_FGCONSTRUCTORMK1_H
#define SFT_FGCONSTRUCTORMK1_H

#include "FGIOUnit.hh"

class FGConstructorMk1: public FGIOUnit {
public:
  FGConstructorMk1()=delete;
  FGConstructorMk1(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConstructorMk1();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
