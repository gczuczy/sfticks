
#ifndef SFT_FGCONVEYORLIFTMK5_H
#define SFT_FGCONVEYORLIFTMK5_H

#include "FGConveyorBelt.hh"

class FGConveyorLiftMk5: public FGConveyorBelt {
public:
  FGConveyorLiftMk5()=delete;
  FGConveyorLiftMk5(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorLiftMk5();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
