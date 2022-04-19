
#ifndef SFT_FGBUILDING_H
#define SFT_FGBUILDING_H

#include "FGEntity.hh"
#include "ObjectReference.hh"
#include "FactoryCustomizationData.hh"
#include "FGInventoryComponent.hh"
#include "FGFactoryConnectionComponent.hh"

#include <vector>
#include <map>
#include <list>

namespace FG {

  class Building: public Entity {
  public:
    Building()=delete;
    Building(EntityType _et, Reader& _reader, ObjectHeader& _fgoh);
    virtual ~Building();
  
    inline float& timeSinceStartStopProducing() {return c_mTimeSinceStartStopProducing;};
    inline float& buildTimeStamp() {return c_mBuildTimeStamp;};
    inline ObjectReference& powerInfo() {return c_mPowerInfo;};
    inline ObjectReference& builtWithRecipe() {return c_mBuiltWithRecipe;};
    inline bool& isProducing() {return c_mIsProducing;};
    inline bool& didFirstTimeUse() {return c_mDidFirstTimeUse;};
    inline std::vector<FactoryConnectionComponentSP>& inputs() {return c_inputs;};
    inline std::vector<FactoryConnectionComponentSP>& outputs() {return c_outputs;};
    inline std::map<std::string, InventoryComponentSP>& inventories() {return c_inventories;};

  protected:
    void defineInputs(const std::vector<std::string>& _compnames);
    void defineOutputs(const std::vector<std::string>& _compnames);
    void defineInventories(const std::list<std::string>& _compnames);

  private:
    //virtual void deserialize(Reader &_reader);

    ObjectReference c_mPowerInfo, c_mBuiltWithRecipe;
    float c_mTimeSinceStartStopProducing, c_mBuildTimeStamp;
    FactoryCustomizationData c_mCustomizationData;
    bool c_mIsProducing, c_mDidFirstTimeUse;

  private:
    std::map<std::string, InventoryComponentSP> c_inventories;
    std::vector<FactoryConnectionComponentSP> c_inputs, c_outputs;
  };

}

#endif
