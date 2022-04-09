
#ifndef SFT_FGFOUNDRYMK1_H
#define SFT_FGFOUNDRYMK1_H

#include "FGIOUnit.hh"

namespace FG {

  class FoundryMk1: public IOUnit {
  public:
    FoundryMk1()=delete;
    FoundryMk1(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~FoundryMk1();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
