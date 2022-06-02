
#ifndef SFT_FGCONVEYORBELT_H
#define SFT_FGCONVEYORBELT_H

#include "FG/Building.hh"
#include "FG/SplinePointData.hh"
#include "FG/FactoryConnectionComponent.hh"
#include "FG/DescObject.hh"

#include <vector>
#include <list>
#include <set>
#include <map>

namespace FG {

  class ConveyorBelt: public Building {\
  public:
    struct BeltItemRef {
      float position=0;
      ObjectReference item;
    };
    typedef std::list<BeltItemRef> BeltItemRefs;
    struct BeltItem {
      BeltItem()=default;
      BeltItem(float _position, DescObjectSP _item);
      BeltItem(float _position, ObjectReference _item);
      float position=0;
      DescObjectSP item;
    };
    typedef std::list<BeltItem> BeltItems;
  public:
    ConveyorBelt()=delete;
    ConveyorBelt(EntityType _et, Reader& _reader, ObjectHeader& _fgoh, int32_t _throughput);
    virtual ~ConveyorBelt();

    inline int32_t throughput() const {return c_throughput;};
    inline std::vector<SplinePointData>& splineData() {return c_mSplineData;};
    inline BeltItems& beltItems() {return c_belt_items;};
    inline float length() const {return c_length;};
    // quickhands
    inline FactoryConnectionComponentSP input() {return inputs()[0];};
    inline FactoryConnectionComponentSP output() {return outputs()[0];};

    virtual void associateComponents();
    virtual void doTick(SFT::tickinfo_t&);
    // overriding Building::recv's generic implementation
    virtual bool recv(DescObjectSP& _item, SFT::tickinfo_t& _tick, FactoryConnectionComponent& _src);

    // tick calculation caching
  private:
    static std::set<uint32_t> c_cache_throughputs;
    static std::map<uint32_t, float> c_cache_movelens;
  public:
    static void doTickCache(SFT::tickinfo_t& _tick);

  private:
    void supplementalHandler(Reader& _r);
    virtual float calcLength();

  private:
    int32_t c_throughput; // items per minute
    std::vector<SplinePointData> c_mSplineData;
    BeltItems c_belt_items;
    BeltItemRefs c_belt_items_ref;
    float c_length=0;
  };

  typedef std::shared_ptr<ConveyorBelt> ConveyorBeltSP;

}

#endif
