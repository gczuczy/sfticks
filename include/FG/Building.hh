
#ifndef SFT_FGBUILDING_H
#define SFT_FGBUILDING_H

#include "FG/Entity.hh"
#include "FG/ObjectReference.hh"
#include "FG/FactoryCustomizationData.hh"
#include "FG/InventoryComponent.hh"
#include "FG/FactoryConnectionComponent.hh"
#include "FG/PowerInfoComponent.hh"

#include <vector>
#include <map>
#include <list>

namespace FG {

  class Building: public Entity {
  public:
    typedef std::vector<FactoryConnectionComponentSP> Connections;
  public:
    Building()=delete;
    Building(EntityType _et, Reader& _reader, ObjectHeader& _fgoh);
    virtual ~Building();
  
    virtual void associateComponents();

    inline float timeSinceStartStopProducing() {return c_mTimeSinceStartStopProducing;};
    inline float buildTimeStamp() {return c_mBuildTimeStamp;};
    inline PowerInfoComponentSP powerInfo() {return c_powerinfo;};
    inline ObjectReference& builtWithRecipe() {return c_mBuiltWithRecipe;};
    inline bool isProducing() {return c_mIsProducing;};
    inline bool didFirstTimeUse() {return c_mDidFirstTimeUse;};
    inline Connections& inputs() {return c_inputs;};
    inline Connections& outputs() {return c_outputs;};
    inline std::map<std::string, InventoryComponentSP>& inventories() {return c_inventories;};

  private:
    //virtual void deserialize(Reader &_reader);

    ObjectReference c_mPowerInfo, c_mBuiltWithRecipe;
    float c_mTimeSinceStartStopProducing=0, c_mBuildTimeStamp=0;
    FactoryCustomizationData c_mCustomizationData;
    bool c_mIsProducing=false, c_mDidFirstTimeUse=false;

  private:
    std::map<std::string, InventoryComponentSP> c_inventories;
    Connections c_inputs, c_outputs;
    PowerInfoComponentSP c_powerinfo;
  };
  typedef std::shared_ptr<Building> BuildingSP;

}

#endif
