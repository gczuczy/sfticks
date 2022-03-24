
#ifndef SFT_FGDRONESTATION_H
#define SFT_FGDRONESTATION_H

#include "FGStorageUnit.hh"

class FGDroneStation: public FGStorageUnit {
public:
  FGDroneStation()=delete;
  FGDroneStation(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGDroneStation();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
