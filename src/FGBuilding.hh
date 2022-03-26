
#ifndef SFT_FGBUILDING_H
#define SFT_FGBUILDING_H

#include "FGEntity.hh"

class FGBuilding: public FGEntity {
public:
  FGBuilding()=delete;
  FGBuilding(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh);
  FGBuilding(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh, const std::set<std::string>& _objdefdecls);
  virtual ~FGBuilding();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
