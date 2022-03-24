
#ifndef SFT_FGASSEMBLERMK1_H
#define SFT_FGASSEMBLERMK1_H

#include "FGIOUnit.hh"

class FGAssemblerMk1: public FGIOUnit {
public:
  FGAssemblerMk1()=delete;
  FGAssemblerMk1(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGAssemblerMk1();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
