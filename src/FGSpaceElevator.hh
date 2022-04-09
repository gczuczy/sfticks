
#ifndef SFT_FGSPACEELEVATOR_H
#define SFT_FGSPACEELEVATOR_H

#include "FGIOUnit.hh"

class FGSpaceElevator: public FGIOUnit {
public:
  FGSpaceElevator()=delete;
  FGSpaceElevator(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGSpaceElevator();

  static std::string objtypename;

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
