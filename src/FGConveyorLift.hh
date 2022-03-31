
#ifndef SFT_FGCONVEYORLIFT_H
#define SFT_FGCONVEYORLIFT_H

#include "FGConveyorBelt.hh"

class FGConveyorLift: public FGConveyorBelt {
public:
  FGConveyorLift()=delete;
  FGConveyorLift(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh, int32_t _throughput);
  virtual ~FGConveyorLift();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
