
#include "FGEnums.hh"

namespace FG {
  template<>
  std::map<ETrainPlatformDockingStatus, std::string> EnumDict<ETrainPlatformDockingStatus>::c_dict = {
    {ETrainPlatformDockingStatus::ETPDS_None, "ETrainPlatformDockingStatus::ETPDS_None"},
    {ETrainPlatformDockingStatus::ETPDS_WaitingToStart, "ETrainPlatformDockingStatus::ETPDS_WaitingToStart"},
    {ETrainPlatformDockingStatus::ETPDS_Loading, "ETrainPlatformDockingStatus::ETPDS_Loading"},
    {ETrainPlatformDockingStatus::ETPDS_Unloading, "ETrainPlatformDockingStatus::ETPDS_Unloading"},
    {ETrainPlatformDockingStatus::ETPDS_WaitingForTransfer, "ETrainPlatformDockingStatus::ETPDS_WaitingForTransfer"},
    {ETrainPlatformDockingStatus::ETPDS_Complete, "ETrainPlatformDockingStatus::ETPDS_Complete"},
    {ETrainPlatformDockingStatus::ETPDS_WaitForTransferCondition, "ETrainPlatformDockingStatus::ETPDS_WaitForTransferCondition"},
    {ETrainPlatformDockingStatus::ETPDS_IdleWaitForTime, "ETrainPlatformDockingStatus::ETPDS_IdleWaitForTime"},
  };

  template<>
  std::map<EFactoryConnectionDirection, std::string> EnumDict<EFactoryConnectionDirection>::c_dict = {
    {EFactoryConnectionDirection::FCD_OUTPUT, "EFactoryConnectionDirection::FCD_OUTPUT"},
    {EFactoryConnectionDirection::FCD_INPUT, "EFactoryConnectionDirection::FCD_INPUT"},
    {EFactoryConnectionDirection::FCD_ANY, "EFactoryConnectionDirection::FCD_ANY"},
    {EFactoryConnectionDirection::FCD_SNAP_ONLY, "EFactoryConnectionDirection::FCD_SNAP_ONLY"},
  };

  template<>
  std::map<EItemTransferringStage, std::string> EnumDict<EItemTransferringStage>::c_dict = {
    {EItemTransferringStage::ITS_LOAD, "EItemTransferringStage::ITS_LOAD"},
    {EItemTransferringStage::ITS_UNLOAD, "EItemTransferringStage::ITS_UNLOAD"},
  };

  template<>
  std::map<ComponentType, std::string> EnumDict<ComponentType>::c_dict = {
    {ComponentType::Generic, "ComponentType::Generic"},
    {ComponentType::FactoryConnection, "ComponentType::FactoryConnection"},
    {ComponentType::Inventory, "ComponentType::Inventory"},
    {ComponentType::PowerInfo, "ComponentType::PowerInfo"},
  };
}
