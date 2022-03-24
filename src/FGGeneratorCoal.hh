
#ifndef SFT_FGGENERATORCOAL_H
#define SFT_FGGENERATORCOAL_H

#include "FGIOUnit.hh"

class FGGeneratorCoal: public FGIOUnit {
public:
  FGGeneratorCoal()=delete;
  FGGeneratorCoal(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGGeneratorCoal();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
