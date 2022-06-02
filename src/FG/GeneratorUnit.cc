
#include "FG/GeneratorUnit.hh"
#include "FG/ObjectProperty.hh"
#include "FG/FloatProperty.hh"
#include "FG/BoolProperty.hh"
#include "SFT/Exception.hh"
#include "misc.hh"

namespace FG {

  GeneratorUnit::GeneratorUnit(EntityType _et, Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(_et, _reader, _fgoh), c_mCurrentFuelAmount(0), c_mHasFuelCached(false) {
    defineProperty(std::make_shared<ObjectProperty>("mFuelInventory", c_mFuelInventory));
    defineProperty(std::make_shared<ObjectProperty>("mCurrentFuelClass", c_mCurrentFuelClass));
    defineProperty(std::make_shared<FloatProperty>("mCurrentFuelAmount", c_mCurrentFuelAmount));
    defineProperty(std::make_shared<BoolProperty>("mHasFuelCached", c_mHasFuelCached));
  }

  GeneratorUnit::~GeneratorUnit() {
  }

  void GeneratorUnit::doTick(SFT::tickinfo_t& _tick) {
    EXCEPTION(strprintf("Check %s", __PRETTY_FUNCTION__));
  }
}
