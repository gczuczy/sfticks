
#ifndef SFT_FGTRAINDOCKINGSTATION_H
#define SFT_FGTRAINDOCKINGSTATION_H

#include "FGStorageUnit.hh"

class FGTrainDockingStation: public FGStorageUnit {
public:
  FGTrainDockingStation()=delete;
  FGTrainDockingStation(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGTrainDockingStation();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
