
#include "EnumProperty.hh"

namespace FG {

  /*
   * ETrainPlatformDockingStatus
   */
  template<>
  EnumProperty<ETrainPlatformDockingStatus>::EnumProperty(const std::string& _name, ETrainPlatformDockingStatus& _value, int32_t _index)
    : PropertyInterface(SavePropertyType::EnumProperty, _name, _index), c_enumtypestr("ETrainPlatformDockingStatus"), c_value(_value) {
  }

  /*
   * EFactoryConnectionDirection
   */
  template<>
  EnumProperty<EFactoryConnectionDirection>::EnumProperty(const std::string& _name, EFactoryConnectionDirection& _value, int32_t _index)
    : PropertyInterface(SavePropertyType::EnumProperty, _name, _index), c_enumtypestr("EFactoryConnectionDirection"), c_value(_value) {
  }

  /*
   * EItemTransferringStage
   */
  template<>
  EnumProperty<EItemTransferringStage>::EnumProperty(const std::string& _name, EItemTransferringStage& _value, int32_t _index)
    : PropertyInterface(SavePropertyType::EnumProperty, _name, _index), c_enumtypestr("EItemTransferringStage"), c_value(_value) {
  }

}
