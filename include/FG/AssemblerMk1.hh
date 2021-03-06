
#ifndef SFT_FGASSEMBLERMK1_H
#define SFT_FGASSEMBLERMK1_H

#include "FG/IOUnit.hh"

namespace FG {

  class AssemblerMk1: public IOUnit {
  public:
    AssemblerMk1()=delete;
    AssemblerMk1(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~AssemblerMk1();

    virtual void doTick(SFT::tickinfo_t& _tick);
    
    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
