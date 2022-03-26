
#ifndef SFT_FGGENERICENTITY_H
#define SFT_FGGENERICENTITY_H

#include "FGEntity.hh"

class FGGenericEntity: public FGEntity {
public:
  FGGenericEntity()=delete;
  FGGenericEntity(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGGenericEntity();

  virtual void deserializeProperties(Reader &_reader);

private:
  virtual void deserialize(Reader &_reader);

private:
  std::string c_properties;
};

#endif
