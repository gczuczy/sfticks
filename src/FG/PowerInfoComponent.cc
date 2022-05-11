
#include "FG/PowerInfoComponent.hh"

#include "FG/FloatProperty.hh"
#include "FG/BoolProperty.hh"

namespace FG {

  std::set<std::string> PowerInfoComponent::pathname{
    "/Script/FactoryGame.PowerInfoComponent",
      "/Script/FactoryGame.FGPowerInfoComponent",
      };
  ComponentType PowerInfoComponent::componenttype(ComponentType::PowerInfo);

  PowerInfoComponent::PowerInfoComponent(Reader& _reader, ObjectHeader& _fgoh)
    : Component(ComponentType::PowerInfo, _reader, _fgoh) {
    defineProperty(std::make_shared<FloatProperty>("mTargetConsumption", c_mTargetConsumption));
    defineProperty(std::make_shared<FloatProperty>("mDynamicProductionCapacity", c_mDynamicProductionCapacity));
    defineProperty(std::make_shared<BoolProperty>("mIsFullBlast", c_mIsFullBlast));
    defineProperty(std::make_shared<FloatProperty>("mBaseProduction", c_mBaseProduction));
  }

  ComponentSP PowerInfoComponent::instantiate(Reader& _reader, ObjectHeader& _fgoh) {
    return std::make_shared<PowerInfoComponent>(_reader, _fgoh);
  }

  std::string PowerInfoComponent::vtypename() {
    return typeid(*this).name();
  }

  std::string PowerInfoComponent::compdetails() {
    std::string rv;

    rv = strprintf("TargetConsumption: %.3f\n", c_mTargetConsumption);
    rv += strprintf("DynamicProductionCapacity: %.3f\n", c_mDynamicProductionCapacity);
    rv += strprintf("isFullBlast: %s\n", c_mIsFullBlast?"yes":"no");
    rv += strprintf("BaseProduction: %.3f\n", c_mBaseProduction);

    return rv;
  }
}
