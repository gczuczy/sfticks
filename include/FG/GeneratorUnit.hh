
#ifndef SFT_FGGENERATORUNIT_H
#define SFT_FGGENERATORUNIT_H

#include "FG/IOUnit.hh"
#include "FG/ObjectReference.hh"

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

    virtual void doTick(SFT::tickinfo_t& _tick);

  private:
    //virtual void deserialize(Reader &_reader);
    float c_mCurrentFuelAmount;
    bool c_mHasFuelCached;
    ObjectReference c_mFuelInventory, c_mCurrentFuelClass;
  };

  typedef std::shared_ptr<GeneratorUnit> GeneratorUnitSP;

}

#endif
