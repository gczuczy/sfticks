
#ifndef SFT_FGRESOURCESINK_H
#define SFT_FGRESOURCESINK_H

#include "FGIOUnit.hh"
#include "ObjectReference.hh"

class FGResourceSink: public FGIOUnit {
public:
  FGResourceSink()=delete;
  FGResourceSink(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGResourceSink();

  inline float& mProducingTimer() {return c_mProducingTimer;};
  inline ObjectReference& mCouponInventory() {return c_mCouponInventory;};

  static std::string objtypename;

private:
  //virtual void deserialize(Reader &_reader);
  float c_mProducingTimer;
  ObjectReference c_mCouponInventory;
};

#endif
