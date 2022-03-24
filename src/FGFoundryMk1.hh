
#ifndef SFT_FGFOUNDRYMK1_H
#define SFT_FGFOUNDRYMK1_H

#include "FGIOUnit.hh"

class FGFoundryMk1: public FGIOUnit {
public:
  FGFoundryMk1()=delete;
  FGFoundryMk1(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGFoundryMk1();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
