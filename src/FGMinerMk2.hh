
#ifndef SFT_FGMINERMK2_H
#define SFT_FGMINERMK2_H

#include "FGMiner.hh"

namespace FG {

  class MinerMk2: public Miner {
  private:
  public:
    MinerMk2()=delete;
    MinerMk2(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~MinerMk2();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
