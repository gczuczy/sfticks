
#ifndef SFT_FGPOWERINFOCOMPONENT_H
#define SFT_FGPOWERINFOCOMPONENT_H

#include "FG/Component.hh"

#include <set>

namespace FG {

  class PowerInfoComponent: public Component {
  public:
    PowerInfoComponent() = delete;
    PowerInfoComponent(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~PowerInfoComponent()=default;
    static ComponentSP instantiate(Reader& _reader, ObjectHeader& _fgoh);

    virtual std::string vtypename();
    virtual std::string compdetails();

    inline float targetConsumption() {return c_mTargetConsumption;};
    inline float dynamicProductionCapacity() {return c_mDynamicProductionCapacity;};
    inline bool isFullBlast() {return c_mIsFullBlast;};
    inline float baseProduction() {return c_mBaseProduction;};

    virtual void finalize();

  public:
    static std::set<std::string> pathname;
    static ComponentType componenttype;

  private:
    float c_mTargetConsumption=1.0, c_mDynamicProductionCapacity=1.0,
      c_mBaseProduction=1.0;
    bool c_mIsFullBlast=true;
  };
  typedef std::shared_ptr<PowerInfoComponent> PowerInfoComponentSP;

}

#endif
