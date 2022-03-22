
#ifndef SFT_FGCONVEYORBELTMK5_H
#define SFT_FGCONVEYORBELTMK5_H

#include "FGConveyorBelt.hh"

class FGConveyorBeltMk5: public FGConveyorBelt {
public:
  FGConveyorBeltMk5()=delete;
  FGConveyorBeltMk5(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorBeltMk5();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
