
#ifndef SFT_FGGENERATORFUEL_H
#define SFT_FGGENERATORFUEL_H

#include "FGGeneratorUnit.hh"

class FGGeneratorFuel: public FGGeneratorUnit {
public:
  FGGeneratorFuel()=delete;
  FGGeneratorFuel(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGGeneratorFuel();

  static std::string objtypename;

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
