
#ifndef SFT_FGCONVEYORLIFTMK3_H
#define SFT_FGCONVEYORLIFTMK3_H

#include "FGConveyorBelt.hh"

class FGConveyorLiftMk3: public FGConveyorBelt {
public:
  FGConveyorLiftMk3()=delete;
  FGConveyorLiftMk3(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorLiftMk3();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
