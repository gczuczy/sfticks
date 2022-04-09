
#ifndef SFT_FGOilRefinery_H
#define SFT_FGOilRefinery_H

#include "FGIOUnit.hh"

class FGOilRefinery: public FGIOUnit {
public:
  FGOilRefinery()=delete;
  FGOilRefinery(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGOilRefinery();

  static std::string objtypename;

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
