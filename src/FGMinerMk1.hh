
#ifndef SFT_FGMINERMK1_H
#define SFT_FGMINERMK1_H

#include "FGMiner.hh"

namespace FG {

  class MinerMk1: public Miner {
  private:
  public:
    MinerMk1()=delete;
    MinerMk1(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~MinerMk1();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
