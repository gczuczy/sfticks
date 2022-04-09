
#ifndef SFT_FGASSEMBLERMK1_H
#define SFT_FGASSEMBLERMK1_H

#include "FGIOUnit.hh"

namespace FG {

  class AssemblerMk1: public IOUnit {
  public:
    AssemblerMk1()=delete;
    AssemblerMk1(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~AssemblerMk1();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
