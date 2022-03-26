
#ifndef SFT_FGCONSTRUCTORMK1_H
#define SFT_FGCONSTRUCTORMK1_H

#include "FGIOUnit.hh"

class FGConstructorMk1: public FGIOUnit {
private:
public:
  FGConstructorMk1()=delete;
  FGConstructorMk1(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConstructorMk1();

  //virtual void deserializeProperties(Reader& _reader);
private:
  //virtual void deserialize(Reader &_reader);
};

#endif
