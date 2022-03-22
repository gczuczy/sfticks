
#ifndef SFT_FGBUILDING_H
#define SFT_FGBUILDING_H

#include "FGEntity.hh"

class FGBuilding: public FGEntity {
public:
  FGBuilding()=delete;
  FGBuilding(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGBuilding()=0;

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
