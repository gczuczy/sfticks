
#ifndef SFT_FGCONVEYORBELTLOGIC_H
#define SFT_FGCONVEYORBELTLOGIC_H

#include "FGBuilding.hh"

// this is an abstraction class for mergers/splitters and alike

// this will need some generic interface for querying the
// inputs and outputs
class FGConveyorBeltLogic: public FGBuilding {
public:
  FGConveyorBeltLogic()=delete;
  FGConveyorBeltLogic(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorBeltLogic();


private:
  //virtual void deserialize(Reader &_reader);
};

typedef std::shared_ptr<FGConveyorBeltLogic> FGConveyorBeltLogicSP;

#endif
