
#ifndef SFT_FGCONSTRUCTORMK1_H
#define SFT_FGCONSTRUCTORMK1_H

#include "FGIOUnit.hh"

namespace FG {

  class ConstructorMk1: public IOUnit {
  private:
  public:
    ConstructorMk1()=delete;
    ConstructorMk1(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ConstructorMk1();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
