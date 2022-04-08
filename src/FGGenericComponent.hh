
#ifndef FST_FGGENERICCOMPONENT_H
#define FST_FGGENERICCOMPONENT_H

#include "FGComponent.hh"

class FGGenericComponent: public FGComponent {
public:
  FGGenericComponent()=delete;
  FGGenericComponent(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGGenericComponent();

  virtual void deserializeProperties(Reader &_reader);

  // debug functions
  void dump(const std::string _file);

private:
  virtual void deserialize(Reader &_reader);

private:
  std::string c_properties;
};

#endif
