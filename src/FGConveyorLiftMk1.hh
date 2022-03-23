
#ifndef SFT_FGCONVEYORLIFTMK1_H
#define SFT_FGCONVEYORLIFTMK1_H

#include "FGConveyorBelt.hh"

class FGConveyorLiftMk1: public FGConveyorBelt {
public:
  FGConveyorLiftMk1()=delete;
  FGConveyorLiftMk1(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorLiftMk1();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
