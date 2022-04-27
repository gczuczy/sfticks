
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
    typedef std::vector<FactoryConnectionComponentSP> Connections;
  public:
    Building()=delete;
    Building(EntityType _et, Reader& _reader, ObjectHeader& _fgoh);
    virtual ~Building();
  
    inline float timeSinceStartStopProducing() {return c_mTimeSinceStartStopProducing;};
    inline float buildTimeStamp() {return c_mBuildTimeStamp;};
    inline ObjectReference& powerInfo() {return c_mPowerInfo;};
    inline ObjectReference& builtWithRecipe() {return c_mBuiltWithRecipe;};
    inline bool isProducing() {return c_mIsProducing;};
    inline bool didFirstTimeUse() {return c_mDidFirstTimeUse;};
    inline Connections& inputs() {return c_inputs;};
    inline Connections& outputs() {return c_outputs;};
    inline std::map<std::string, InventoryComponentSP>& inventories() {return c_inventories;};

  protected:
    void defineInputs(const std::vector<std::string>& _compnames);
    void defineOutputs(const std::vector<std::string>& _compnames);
    void defineInventories(const std::list<std::string>& _compnames);

  private:
    //virtual void deserialize(Reader &_reader);

    ObjectReference c_mPowerInfo, c_mBuiltWithRecipe;
    float c_mTimeSinceStartStopProducing=0, c_mBuildTimeStamp=0;
    FactoryCustomizationData c_mCustomizationData;
    bool c_mIsProducing=false, c_mDidFirstTimeUse=false;

  private:
    std::map<std::string, InventoryComponentSP> c_inventories;
    Connections c_inputs, c_outputs;
  };
  typedef std::shared_ptr<Building> BuildingSP;

}

#endif
