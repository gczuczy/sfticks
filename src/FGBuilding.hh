
#ifndef SFT_FGBUILDING_H
#define SFT_FGBUILDING_H

#include "FGEntity.hh"
#include "ObjectReference.hh"
#include "GenericStruct.hh"
#include "FGComponent.hh"

class FGBuilding: public FGEntity {
public:
  // Component classes
  class InOutPort: public FGComponent {
  public:
    InOutPort() = delete;
    InOutPort(Reader& _reader, FGObjectHeader& _fgoh);
    virtual ~InOutPort()=default;
    static FGComponentSP instantiate(Reader& _reader, FGObjectHeader& _fgoh);

    inline ObjectReference& mConnectedComponent() {return c_mConnectedComponent;};
    inline ObjectReference& mConnectionInventory() {return c_mConnectionInventory;};
    inline int32_t mInventoryAccessIndex() const {return c_mInventoryAccessIndex;};

  private:
    ObjectReference c_mConnectedComponent, c_mConnectionInventory;
    int32_t c_mInventoryAccessIndex;
  };
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
  inline float& mBuildTimeStamp() {return c_mBuildTimeStamp;};
  inline ObjectReference& mPowerInfo() {return c_mPowerInfo;};
  inline ObjectReference& mBuiltWithRecipe() {return c_mBuiltWithRecipe;};
  inline bool& mIsProducing() {return c_mIsProducing;};
  inline bool& mDidFirstTimeUse() {return c_mDidFirstTimeUse;};

private:
  //virtual void deserialize(Reader &_reader);

  ObjectReference c_mPowerInfo, c_mBuiltWithRecipe;
  float c_mTimeSinceStartStopProducing, c_mBuildTimeStamp;
  GenericStructSP c_mCustomizationData;
  bool c_mIsProducing, c_mDidFirstTimeUse;
};

#endif
