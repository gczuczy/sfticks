
#ifndef SFT_FGBUILDING_H
#define SFT_FGBUILDING_H

#include "FGEntity.hh"

class FGBuilding: public FGEntity {
protected:
  struct FactoryCustomizationData {
    FactoryCustomizationData() = default;
    FactoryCustomizationData(const FactoryCustomizationData&) = default;
    //FactoryCustomizationData(FactoryCustomizationData&&) = default;
    FactoryCustomizationData(Reader &);
    //    FactoryCustomizationData& operator=(const FactoryCustomizationData&) = default;
    std::string SwatchDesc_ns;
    std::string SwatchDesc;
  };
public:
  FGBuilding()=delete;
  FGBuilding(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGBuilding();
  
  inline float& mTimeSinceStartStopProducing() {return c_mTimeSinceStartStopProducing;};
  inline bool& mIsProducing() {return c_mIsProducing;};
  inline bool& mDidFirstTimeUse() {return c_mDidFirstTimeUse;};
  inline float& mBuildTimeStamp() {return c_mBuildTimeStamp;};

private:
  void defPropLoaders();
  //virtual void deserialize(Reader &_reader);

  FactoryCustomizationData c_mCustomizationData;
  float c_mTimeSinceStartStopProducing, c_mBuildTimeStamp;
  bool c_mIsProducing, c_mDidFirstTimeUse;
};

#endif
