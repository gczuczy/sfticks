
#ifndef FST_FGGENERICCOMPONENT_H
#define FST_FGGENERICCOMPONENT_H

#include "FGComponent.hh"

class FGGenericComponent: public FGComponent {
public:
  FGGenericComponent()=delete;
  FGGenericComponent(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGGenericComponent();

private:
  virtual void deserialize(Reader &_reader);
};

#endif
