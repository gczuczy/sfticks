
#ifndef SFT_FGGENERATORNUCLEAR_H
#define SFT_FGGENERATORNUCLEAR_H

#include "FGGeneratorUnit.hh"

class FGGeneratorNuclear: public FGGeneratorUnit {
public:
  FGGeneratorNuclear()=delete;
  FGGeneratorNuclear(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGGeneratorNuclear();

  static std::string objtypename;

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
