
#ifndef SFT_FGGENERATORUNIT_H
#define SFT_FGGENERATORUNIT_H

#include "FGIOUnit.hh"
#include "ObjectReference.hh"

namespace FG {

  /*
    This is a base class for Input/Output units.
    An input-output unit is everything that has at least input or output, and
    does something with it, apart from storing it.
  */
  class GeneratorUnit: public IOUnit {
  public:
    GeneratorUnit()=delete;
    GeneratorUnit(EntityType _et, Reader& _reader, ObjectHeader& _fgoh);
    virtual ~GeneratorUnit();

    inline float& mCurrentFuelAmount() {return c_mCurrentFuelAmount;};
    inline bool& mHasFuelCached() {return c_mHasFuelCached;};
    inline InventoryComponentSP FuelInventory() {return c_fuel_inventory;};

  private:
    //virtual void deserialize(Reader &_reader);
    float c_mCurrentFuelAmount;
    bool c_mHasFuelCached;
    ObjectReference c_mFuelInventory, c_mCurrentFuelClass;

    InventoryComponentSP c_fuel_inventory;
  };

  typedef std::shared_ptr<GeneratorUnit> GeneratorUnitSP;

}

#endif
