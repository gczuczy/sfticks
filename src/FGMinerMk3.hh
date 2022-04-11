
#ifndef SFT_FGMINERMK3_H
#define SFT_FGMINERMK3_H

#include "FGMiner.hh"

namespace FG {

  class MinerMk3: public Miner {
  private:
  public:
    MinerMk3()=delete;
    MinerMk3(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~MinerMk3();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
