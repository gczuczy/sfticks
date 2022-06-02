
#ifndef SFT_FGSMELTERMK1_H
#define SFT_FGSMELTERMK1_H

#include "FG/IOUnit.hh"

namespace FG {

  class SmelterMk1: public IOUnit {
  public:
    SmelterMk1()=delete;
    SmelterMk1(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~SmelterMk1();

    virtual void doTick(SFT::tickinfo_t& _tick);

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
