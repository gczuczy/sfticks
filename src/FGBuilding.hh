
#ifndef SFT_FGBUILDING_H
#define SFT_FGBUILDING_H

#include "FGEntity.hh"
#include "ObjectReference.hh"
#include "FactoryCustomizationData.hh"

namespace FG {

  class Building: public Entity {
  public:
    Building()=delete;
    Building(EntityType _et, Reader& _reader, ObjectHeader& _fgoh);
    virtual ~Building();
  
    inline float& mTimeSinceStartStopProducing() {return c_mTimeSinceStartStopProducing;};
    inline float& mBuildTimeStamp() {return c_mBuildTimeStamp;};
    inline ObjectReference& mPowerInfo() {return c_mPowerInfo;};
    inline ObjectReference& mBuiltWithRecipe() {return c_mBuiltWithRecipe;};
    inline bool& mIsProducing() {return c_mIsProducing;};
    inline bool& mDidFirstTimeUse() {return c_mDidFirstTimeUse;};

  private:
    //virtual void deserialize(Reader &_reader);

    ObjectReference c_mPowerInfo, c_mBuiltWithRecipe;
    float c_mTimeSinceStartStopProducing, c_mBuildTimeStamp;
    FactoryCustomizationData c_mCustomizationData;
    bool c_mIsProducing, c_mDidFirstTimeUse;
  };

}

#endif
