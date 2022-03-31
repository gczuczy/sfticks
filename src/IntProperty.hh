
#ifndef SFT_INTPROPERTY_H
#define SFT_INTPROPERTY_H

#include "PropertyInterface.hh"

class IntProperty: public PropertyInterface {
public:
  IntProperty() = delete;
  IntProperty(const std::string& _name, int32_t& _value, int32_t _index=0);
  virtual ~IntProperty()=default;

  virtual void deserialize(Reader& _reader, int32_t _size);
  virtual void deserializeData(Reader& _reader);

private:
  int32_t& c_value;
};

#endif