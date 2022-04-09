
#ifndef SFT_FGPACKAGER_H
#define SFT_FGPACKAGER_H

#include "FGIOUnit.hh"

namespace FG {

  class Packager: public IOUnit {
  public:
    Packager()=delete;
    Packager(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~Packager();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
