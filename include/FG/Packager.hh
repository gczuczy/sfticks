
#ifndef SFT_FGPACKAGER_H
#define SFT_FGPACKAGER_H

#include "FG/IOUnit.hh"

namespace FG {

  class Packager: public IOUnit {
  public:
    Packager()=delete;
    Packager(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~Packager();

    virtual void doTick(SFT::tickinfo_t& _tick);

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
