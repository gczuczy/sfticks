
#ifndef SFT_FGGENERATORNUCLEAR_H
#define SFT_FGGENERATORNUCLEAR_H

#include "FGIOUnit.hh"

class FGGeneratorNuclear: public FGIOUnit {
public:
  FGGeneratorNuclear()=delete;
  FGGeneratorNuclear(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGGeneratorNuclear();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
