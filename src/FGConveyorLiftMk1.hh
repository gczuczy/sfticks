
#ifndef SFT_FGCONVEYORLIFTMK1_H
#define SFT_FGCONVEYORLIFTMK1_H

#include "FGConveyorLift.hh"

class FGConveyorLiftMk1: public FGConveyorLift {
public:
  FGConveyorLiftMk1()=delete;
  FGConveyorLiftMk1(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorLiftMk1();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
