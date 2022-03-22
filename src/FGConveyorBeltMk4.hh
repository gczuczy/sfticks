
#ifndef SFT_FGCONVEYORBELTMK4_H
#define SFT_FGCONVEYORBELTMK4_H

#include "FGConveyorBelt.hh"

class FGConveyorBeltMk4: public FGConveyorBelt {
public:
  FGConveyorBeltMk4()=delete;
  FGConveyorBeltMk4(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorBeltMk4();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
