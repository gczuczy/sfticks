
#ifndef SFT_FGRESOURCESINK_H
#define SFT_FGRESOURCESINK_H

#include "FG/IOUnit.hh"
#include "FG/ObjectReference.hh"

namespace FG {

  class ResourceSink: public IOUnit {
  public:
    ResourceSink()=delete;
    ResourceSink(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ResourceSink();

    inline float& mProducingTimer() {return c_mProducingTimer;};
    inline ObjectReference& mCouponInventory() {return c_mCouponInventory;};

    virtual void doTick(SFT::tickinfo_t& _tick);

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
    float c_mProducingTimer;
    ObjectReference c_mCouponInventory;
  };

}

#endif
