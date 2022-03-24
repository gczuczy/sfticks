
#ifndef SFT_FGSMELTERMK1_H
#define SFT_FGSMELTERMK1_H

#include "FGIOUnit.hh"

class FGSmelterMk1: public FGIOUnit {
public:
  FGSmelterMk1()=delete;
  FGSmelterMk1(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGSmelterMk1();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
