
#ifndef SFT_FGSTORAGEUNIT_H
#define SFT_FGSTORAGEUNIT_H

#include "FGBuilding.hh"

/*
  This is a base class for Input/Output units.
  An input-output unit is everything that has at least input or output, and
  does something with it, apart from storing it.
 */
class FGStorageUnit: public FGBuilding {
public:
  FGStorageUnit()=delete;
  FGStorageUnit(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh, int32_t _capacity);
  virtual ~FGStorageUnit();

  inline int32_t capacity() const {return c_capacity;};

private:
  int32_t c_capacity;
  //virtual void deserialize(Reader &_reader);
};

typedef std::shared_ptr<FGStorageUnit> FGStorageUnitSP;

#endif
