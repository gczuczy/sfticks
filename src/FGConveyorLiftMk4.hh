
#ifndef SFT_FGCONVEYORLIFTMK4_H
#define SFT_FGCONVEYORLIFTMK4_H

#include "FGConveyorLift.hh"

class FGConveyorLiftMk4: public FGConveyorLift {
public:
  FGConveyorLiftMk4()=delete;
  FGConveyorLiftMk4(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorLiftMk4();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
