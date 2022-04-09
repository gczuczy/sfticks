
#ifndef SFT_FGENUMS_H
#define SFT_FGENUMS_H

enum class ETrainPlatformDockingStatus: int8_t {
  ETDS_WaitingToStart=0,
};

enum class EFactoryConnectionDirection: int8_t {
  FCD_OUTPUT=0,
  FCD_INPUT,
};

#endif
