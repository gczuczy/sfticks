
#ifndef SFT_FGMINER_H
#define SFT_FGMINER_H

#include "FG/IOUnit.hh"
#include "FG/ObjectReference.hh"

namespace FG {

  /*
    This is a base class for Input/Output units.
    An input-output unit is everything that has at least input or output, and
    does something with it, apart from storing it.
  */
  class Miner: public IOUnit {
  public:
    Miner()=delete;
    Miner(EntityType _et, Reader& _reader, ObjectHeader& _fgoh);
    virtual ~Miner();

    inline float& mExtractStartupTimer() {return c_mExtractStartupTimer;};
    inline float& mCurrentExtractProgress() {return c_mCurrentExtractProgress;};
    inline ObjectReference& mmExtractableResource() {return c_mExtractableResource;};

    virtual void doTick(SFT::tickinfo_t& _tick);

  private:
    //virtual void deserialize(Reader &_reader);
    float c_mExtractStartupTimer=0, c_mCurrentExtractProgress=0;
    ObjectReference c_mExtractableResource;

  };
  typedef std::shared_ptr<Miner> MinerSP;

}

#endif
