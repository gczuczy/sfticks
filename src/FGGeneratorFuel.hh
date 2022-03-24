
#ifndef SFT_FGGENERATORFUEL_H
#define SFT_FGGENERATORFUEL_H

#include "FGIOUnit.hh"

class FGGeneratorFuel: public FGIOUnit {
public:
  FGGeneratorFuel()=delete;
  FGGeneratorFuel(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGGeneratorFuel();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
