
#ifndef SFT_FGTREEGIFTPRODUCER_H
#define SFT_FGTREEGIFTPRODUCER_H

#include "FG/Miner.hh"

namespace FG {

  class TreeGiftProducer: public Miner {
  private:
  public:
    TreeGiftProducer()=delete;
    TreeGiftProducer(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~TreeGiftProducer();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
