
#ifndef SFT_FGIOUNIT_H
#define SFT_FGIOUNIT_H

#include "FGBuilding.hh"

/*
  This is a base class for Input/Output units.
  An input-output unit is everything that has at least input or output, and
  does something with it, apart from storing it.
 */
class FGIOUnit: public FGBuilding {
public:
  FGIOUnit()=delete;
  FGIOUnit(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh);
  FGIOUnit(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh, const std::set<std::string>& _objdefdecls);
  virtual ~FGIOUnit();

private:
  //virtual void deserialize(Reader &_reader);
};

typedef std::shared_ptr<FGIOUnit> FGIOUnitSP;

#endif
