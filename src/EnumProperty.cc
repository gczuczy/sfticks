
#include "EnumProperty.hh"

namespace FG {

  /*
   * ETrainPlatformDockingStatus
   */
  template<>
  std::map<ETrainPlatformDockingStatus, std::string> EnumProperty<ETrainPlatformDockingStatus>::c_strmap = {
    {ETrainPlatformDockingStatus::ETDS_WaitingToStart, "ETrainPlatformDockingStatus::ETPDS_WaitingToStart"}
  };

  template<>
  EnumProperty<ETrainPlatformDockingStatus>::EnumProperty(const std::string& _name, ETrainPlatformDockingStatus& _value, int32_t _index)
    : PropertyInterface(SavePropertyType::EnumProperty, _name, _index), c_enumtypestr("ETrainPlatformDockingStatus"), c_value(_value) {
  }

  /*
   * EFactoryConnectionDirection
   */
  template<>
  std::map<EFactoryConnectionDirection, std::string> EnumProperty<EFactoryConnectionDirection>::c_strmap = {
    {EFactoryConnectionDirection::FCD_OUTPUT, "EFactoryConnectionDirection::FCD_OUTPUT"},
    {EFactoryConnectionDirection::FCD_INPUT, "EFactoryConnectionDirection::FCD_INPUT"}
  };

  template<>
  EnumProperty<EFactoryConnectionDirection>::EnumProperty(const std::string& _name, EFactoryConnectionDirection& _value, int32_t _index)
    : PropertyInterface(SavePropertyType::EnumProperty, _name, _index), c_enumtypestr("EFactoryConnectionDirection"), c_value(_value) {
  }


#if 0
  template<T>
  std::map<T, std::string> EnumProperty<T>::c_strmap;
#endif

}
