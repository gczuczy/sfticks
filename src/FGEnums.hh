
#ifndef SFT_FGENUMS_H
#define SFT_FGENUMS_H

#include <map>
#include <string>

#include <stdio.h>
#include "misc.hh"
#include "Exception.hh"
#include "FGComponent.hh"

namespace FG {

  enum class ETrainPlatformDockingStatus: int8_t {
    ETPDS_None=0,
    ETPDS_WaitingToStart,
    ETPDS_Loading,
    ETPDS_Unloading,
    ETPDS_WaitingForTransfer,
    ETPDS_Complete,
    ETPDS_WaitForTransferCondition,
    ETPDS_IdleWaitForTime,
  };

  enum class EFactoryConnectionDirection: int8_t {
    FCD_OUTPUT=0,
    FCD_INPUT,
    FCD_ANY,
    FCD_SNAP_ONLY,
  };

  enum class EItemTransferringStage: int8_t {
    ITS_LOAD=0,
    ITS_UNLOAD,
  };

  template<typename T>
  class EnumDict {
  public:
    EnumDict()=default;
    ~EnumDict()=default;
    
    static std::string tostr(T _val) {
      return c_dict.find(_val)->second;
    }
    static T fromstr(const std::string& _val) {
      for (auto it: c_dict) {
	if ( it.second == _val ) return it.first;
      }
      EXCEPTION(strprintf("Enum value not found: %s", _val.c_str()));
    }

  private:
    static std::map<T, std::string> c_dict;
  };

  template<>
  std::map<ETrainPlatformDockingStatus, std::string> EnumDict<ETrainPlatformDockingStatus>::c_dict;
  template<>
  std::map<EFactoryConnectionDirection, std::string> EnumDict<EFactoryConnectionDirection>::c_dict;
  template<>
  std::map<EItemTransferringStage, std::string> EnumDict<EItemTransferringStage>::c_dict;
  template<>
  std::map<ComponentType, std::string> EnumDict<ComponentType>::c_dict;
  
}

#endif
