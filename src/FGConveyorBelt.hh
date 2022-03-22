
#ifndef SFT_FGCONVEYORBELT_H
#define SFT_FGCONVEYORBELT_H

#include "FGBuilding.hh"

class FGConveyorBelt: public FGBuilding {
public:
  FGConveyorBelt()=delete;
  FGConveyorBelt(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh, int32_t _throughput);
  virtual ~FGConveyorBelt() = 0;

  inline int32_t throughput() const {return c_throughput;};

private:
  int32_t c_throughput; // items per minute
  //virtual void deserialize(Reader &_reader);
};

#endif
