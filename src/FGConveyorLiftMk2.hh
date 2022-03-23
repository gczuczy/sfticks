
#ifndef SFT_FGCONVEYORLIFTMK2_H
#define SFT_FGCONVEYORLIFTMK2_H

#include "FGConveyorBelt.hh"

class FGConveyorLiftMk2: public FGConveyorBelt {
public:
  FGConveyorLiftMk2()=delete;
  FGConveyorLiftMk2(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorLiftMk2();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
