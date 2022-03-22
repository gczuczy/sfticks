
#ifndef SFT_FGGENERICENTITY_H
#define SFT_FGGENERICENTITY_H

#include "FGEntity.hh"

class FGGenericEntity: public FGEntity {
public:
  FGGenericEntity()=delete;
  FGGenericEntity(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGGenericEntity();

private:
  virtual void deserialize(Reader &_reader);
};

#endif
